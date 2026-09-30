#include "SceneManager.h"

#include <chrono>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <cassert>

#include "../../Scene/SceneTitle.h"
#include "../../Scene/SceneGame.h"
#include "../../Scene/SceneGameOver.h"
#include "../../Scene/SceneGameClear.h"
#include "ResourceManager.h"
#include "../System/Collision.h"
#include "../Decoration/SoundManager.h"
#include "../../Object/Manager/CollisionManager.h"
#include "../System/TimeManager.h"
#include "Camera.h"

SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new SceneManager();
    }
    instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
    return *instance_;
}

void SceneManager::Init(void)
{
    // 各マネジャーの生成
    Collision::CreateInstance();
    SoundManager::CreateInstance();
    TimeManager::CreateInstance();
    CollisionManager::CreateInstance();

    sceneId_ = SCENE_ID::TITLE;
    waitSceneId_ = SCENE_ID::NONE;

    fader_ = std::make_unique<Fader>();
    fader_->Init();

    camera_ = std::make_unique<Camera>();
    camera_->Init();

    scene_ = new SceneTitle();
    scene_->Init();

    isSceneChanging_ = false;

    preTime_ = std::chrono::system_clock::now();

    // 3D用の初期化処理
    Init3D();

    // 初期シーンの設定
    DoChangeScene(SCENE_ID::TITLE);
}

void SceneManager::Init3D(void)
{
    const int BACKGROUND_COLOR_RED = 0;   // 背景色(赤)
    const int BACKGROUND_COLOR_GREEN = 0; // 背景色(緑)
    const int BACKGROUND_COLOR_BLUE = 0;  // 背景色(青)
    SetBackgroundColor(BACKGROUND_COLOR_RED, BACKGROUND_COLOR_GREEN, BACKGROUND_COLOR_BLUE);

    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);
    SetUseBackCulling(true);
    SetUseLighting(true);
    SetLightEnable(true);

    const int FOG_COLOR_RED = 5;          // フォグ色(赤)
    const int FOG_COLOR_GREEN = 5;        // フォグ色(緑)
    const int FOG_COLOR_BLUE = 5;         // フォグ色(青)
    const float FOG_DISTANCE_START = 10000.0f; // フォグの開始距離
    const float FOG_DISTANCE_END = 20000.0f;   // フォグの終了距離

    SetFogEnable(true);
    SetFogColor(FOG_COLOR_RED, FOG_COLOR_GREEN, FOG_COLOR_BLUE);
    SetFogStartEnd(FOG_DISTANCE_START, FOG_DISTANCE_END);
}

void SceneManager::Update(void)
{
    TimeManager::GetInstance().Update();

    if (scene_ == nullptr)
    {
        return;
    }

    auto nowTime = std::chrono::system_clock::now();

    const double NANOSECONDS_PER_SECOND = 1000000000.0; 

    // 100文字を超過しないよう改行してデルタタイムを算出
    auto durationCount = std::chrono::duration_cast<std::chrono::nanoseconds>(
        nowTime - preTime_).count();

    deltaTime_ = static_cast<float>(durationCount / NANOSECONDS_PER_SECOND);

    preTime_ = nowTime;

    fader_->Update();

    if (isSceneChanging_)
    {
        Fade();
    }
    else
    {
        scene_->Update();
    }

    camera_->Update();
}

void SceneManager::Draw(void)
{
    // 描画先グラフィック領域の指定
    // (3D描画で使用するカメラの設定などがリセットされる)
    SetDrawScreen(DX_SCREEN_BACK);

    // フロントバッファの画像を消去
    ClearDrawScreen();

    // カメラの設定
    camera_->SetBeforeDraw();

    // ゲーム内容描画
    scene_->Draw();

    // 暗転・明転
    fader_->Draw();

    // カメラ座標
    camera_->Draw();
}

void SceneManager::Destroy(void)
{
    scene_->Release();
    delete scene_;

    SoundManager::GetInstance().Destroy();
    CollisionManager::GetInstance().Destroy();
    TimeManager::GetInstance().Destroy();

    delete instance_;
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{
    // フェード処理が終わってからシーンを変える場合もあるため、
    // 遷移先シーンをメンバ変数に保持
    waitSceneId_ = nextId;

    // フェードアウト(暗転)を開始する
    fader_->SetFade(Fader::STATE::FADE_OUT);
    isSceneChanging_ = true;
}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
    return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
    return deltaTime_;
}

SceneBase* SceneManager::GetScene(void) const
{
    return scene_;
}

std::shared_ptr<Camera> SceneManager::GetCamera(void) const
{
    return camera_;
}

SceneManager::SceneManager(void)
{
    sceneId_ = SCENE_ID::NONE;
    waitSceneId_ = SCENE_ID::NONE;

    scene_ = nullptr;
    fader_ = nullptr;

    isSceneChanging_ = false;

    const float DEFAULT_DELTA_TIME = 1.0f / 60.0f; 
    deltaTime_ = DEFAULT_DELTA_TIME;
}

void SceneManager::ResetDeltaTime(void)
{
    const float DEFAULT_DELTA_TIME = 1.0f / 60.0f; 
    deltaTime_ = DEFAULT_DELTA_TIME;
    preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{
    auto& resourceManager = ResourceManager::GetInstance();

    // リソースの解放
    resourceManager.Release();
    SoundManager::GetInstance().Release();

    // シーンを変更する
    sceneId_ = sceneId;

    // 現在のシーンを解放
    if (scene_ != nullptr)
    {
        scene_->Release();
        delete scene_;
    }

    switch (sceneId_)
    {
    case SceneManager::SCENE_ID::TITLE:
        scene_ = new SceneTitle();
        resourceManager.InitTitle();
        break;

    case SceneManager::SCENE_ID::GAME:
        scene_ = new SceneGame();
        resourceManager.InitGame();
        break;

    case SceneManager::SCENE_ID::GAMECLEAR:
        scene_ = new SceneGameClear();
        resourceManager.InitGameClear();
        break;

    case SceneManager::SCENE_ID::GAMEOVER:
        scene_ = new SceneGameOver();
        resourceManager.InitGameOver();
        break;

    case SceneManager::SCENE_ID::NONE:
        // 警告回避
        break;
    }

    scene_->Init();

    ResetDeltaTime();

    waitSceneId_ = SCENE_ID::NONE;
}

void SceneManager::Fade(void)
{
    Fader::STATE fadeState = fader_->GetState();

    switch (fadeState)
    {
    case Fader::STATE::FADE_IN:
        // 明転中
        if (fader_->IsEnd())
        {
            // 明転が終了したら、フェード処理終了
            fader_->SetFade(Fader::STATE::NONE);
            isSceneChanging_ = false;
        }
        break;

    case Fader::STATE::FADE_OUT:
        // 暗転中
        if (fader_->IsEnd())
        {
            // 完全に暗転してからシーン遷移
            DoChangeScene(waitSceneId_);

            // 暗転から明転へ
            fader_->SetFade(Fader::STATE::FADE_IN);
        }
        break;

    case Fader::STATE::NONE:
        break;
    }
}