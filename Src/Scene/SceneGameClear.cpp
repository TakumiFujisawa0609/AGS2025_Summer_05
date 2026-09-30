#include "SceneGameClear.h"

#include <DxLib.h>

#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/Decoration/SoundManager.h"
#include "../DrawUI/SceneUI/SceneUI.h"

SceneGameClear::SceneGameClear(void)
{
}

void SceneGameClear::Init(void)
{
    ui_ = std::make_unique<SceneUi>();
    ui_->AddCharacter("Spaceを押して開始");

    const int BGM_VOLUME = 40;                              // BGMの音量
    const int SE_VOLUME = 30;                               // 決定SEの音量

    auto& soundManager = SoundManager::GetInstance();
    auto& resourceManager = ResourceManager::GetInstance();

    soundManager.Add(
        SoundManager::TYPE::BGM,
        SoundManager::SOUND::BGM_TITLE,
        resourceManager.Load(ResourceManager::SRC::BGM_TITLE).handleId_
    );
    soundManager.Add(
        SoundManager::TYPE::SE,
        SoundManager::SOUND::SE_PUSH,
        resourceManager.Load(ResourceManager::SRC::SE_PUSH).handleId_
    );

    soundManager.AdjustVolume(SoundManager::SOUND::BGM_TITLE, BGM_VOLUME);
    soundManager.AdjustVolume(SoundManager::SOUND::SE_PUSH, SE_VOLUME);

    soundManager.Play(SoundManager::SOUND::BGM_TITLE);
}

void SceneGameClear::Update(void)
{
    auto& soundManager = SoundManager::GetInstance();

    if (InputManager::GetInstance().IsTriggerDown(KEY_INPUT_RETURN))
    {
        soundManager.Play(SoundManager::SOUND::SE_PUSH);
        soundManager.Stop(SoundManager::SOUND::BGM_TITLE);

        SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);

        return;
    }
}

void SceneGameClear::Draw(void)
{
    const int TEXT_POSITION_X = 0;                          // テキスト描画位置X
    const int TEXT_POSITION_Y = 0;                          // テキスト描画位置Y
    const int TEXT_COLOR_WHITE = 0xffffff;                  // 白色テキスト

    DrawFormatString(TEXT_POSITION_X, TEXT_POSITION_Y, TEXT_COLOR_WHITE, "ゲームクリア");
}

void SceneGameClear::Release(void)
{
}

void SceneGameClear::DrawDebug(void)
{
}