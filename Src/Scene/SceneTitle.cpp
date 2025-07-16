#include "SceneTitle.h"

#include <DxLib.h>
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/Decoration/SoundManager.h"
#include "../Manager/Generic/Camera.h"
#include "../DrawUI/SceneUI/SceneUI.h"
#include "../Object/Grid.h"
#include "../Application.h"

SceneTitle::SceneTitle(void)
{
    logo_ = -1;
    grid_ = nullptr;
    isDecided_ = false;
    blackAlpha_ = 0;
    operationHandle_ = -1;
}

void SceneTitle::Init(void)
{
    
    auto camera = SceneManager::GetInstance().GetCamera();
    camera->ChangeMode(Camera::MODE::FREE);


    grid_ = new Grid();
    grid_->Init();

    ui_ = std::make_unique<SceneUi>();
    ui_->AddCharctor("開始");
    ui_->AddCharctor("遊び方");
    ui_->AddCharctor("操作説明");
    ui_->AddCharctor("クレジット");

    auto& sound = SoundManager::GetInstance();
    auto& res = ResourceManager::GetInstance();

    sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_TITLE, res.Load(ResourceManager::SRC::BGM_TITLE).handleId_);
    sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_PUSH, res.Load(ResourceManager::SRC::SE_PUSH).handleId_);
    sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_SELECT, res.Load(ResourceManager::SRC::SE_SELECT).handleId_);
    sound.AdjustVolume(SoundManager::SOUND::BGM_TITLE, 40);
    sound.AdjustVolume(SoundManager::SOUND::SE_PUSH, 30);
    sound.AdjustVolume(SoundManager::SOUND::SE_SELECT, 30);

    sound.Play(SoundManager::SOUND::BGM_TITLE);

    movieHandle_ = LoadGraph((Application::PATH_MOVIE + "TitleMovie.mp4").c_str());
    PlayMovieToGraph(movieHandle_, TRUE);
    SetMovieVolumeToGraph(movieHandle_, 255);


    logo_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TYTLE_LOGO).handleId_;
    operationHandle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::OPERATION).handleId_;
}

void SceneTitle::Update(void)
{
    auto& sound = SoundManager::GetInstance();
    auto& input = InputManager::GetInstance();

    if (showBlackBackground_)
    {
        // 黒背景表示中はXキーで戻る処理のみ許可
        if (input.IsTrgDown(KEY_INPUT_X))
        {
            sound.Play(SoundManager::SOUND::SE_CANCEL);
            showBlackBackground_ = false; // メニュー表示に戻る
        }
        return; // それ以外は操作無効化
    }

    // カーソル操作（上下キー）と決定処理はここだけで動く
    int currentIndex = ui_->GetCurrentIndex();
    int maxIndex = ui_->GetMaxIndex() - 1;

    if (input.IsTrgDown(KEY_INPUT_UP))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        currentIndex--;
        if (currentIndex < 0) currentIndex = maxIndex;
        ui_->SetCurrentIndex(currentIndex);
    }
    else if (input.IsTrgDown(KEY_INPUT_DOWN))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        currentIndex++;
        if (currentIndex > maxIndex) currentIndex = 0;
        ui_->SetCurrentIndex(currentIndex);
    }

    if (input.IsTrgDown(KEY_INPUT_RETURN))
    {
        int selected = ui_->GetCurrentIndex();
        if (selected != 0)
        {
            showBlackBackground_ = true;
        }
        else
        {
            sound.Play(SoundManager::SOUND::SE_PUSH);
            sound.Stop(SoundManager::SOUND::BGM_TITLE);
            SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
            return;
        }
    }

    ui_->FontBlinking();
}

void SceneTitle::Draw(void)
{
#ifdef _DEBUG
    DrawDebug();
    grid_->Draw();
#endif

    // 背景動画
    DrawRotaGraph3(0, 0, 0, 0, 0.8f, 0.8f, 0, movieHandle_, FALSE);

    // 黒背景表示
    if (showBlackBackground_)
    {
        DrawBox(0, 0, Application::DEFA_SCREEN_SIZE_X, Application::DEFA_SCREEN_SZIE_Y, GetColor(0, 0, 0), TRUE);
    }

   

    // UIは黒背景時は非表示
    if (!showBlackBackground_)
    {
        // タイトルロゴ
        DrawRotaGraph(Application::SCREEN_SIZE_X / 2 + 55, Application::SCREEN_SIZE_Y / 2, 1.0, 0.0, logo_, true);
        ui_->Draw();
    }

    if (ui_->GetCurrentIndex() == 2 && showBlackBackground_)
    {
        DrawRotaGraph3(20,20, 0, 0, 1.2f, 1.2f, 0,operationHandle_, true);
    }
}

void SceneTitle::Release(void)
{
    DeleteGraph(movieHandle_);
    grid_->Release();
    delete grid_;
    grid_ = nullptr;
}

void SceneTitle::DrawDebug(void)
{
    // 必要に応じて
}
