#include "TeleportUI.h"

#include <DxLib.h>
#include <cstring>
#include "../../Application.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../DrawUI/Font.h"
#include "../../Object/Manager/StageManager.h"
#include "../../Object/PlayerStop.h"
#include "../../Object/player.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Manager/Generic/ResourceManager.h"

TeleportUI::TeleportUI(StageManager* stageManager, Player* player)
    : isVisible_(false)
    , selected_(DESTINATION::ATELIER)
    , stageManager_(stageManager)
    , player_(player)
{
}

void TeleportUI::Init(void)
{
    auto& sound = SoundManager::GetInstance();
    auto& resourceManager = ResourceManager::GetInstance();

    constexpr int SE_VOLUME = 50; // SEの音量

    selected_ = DESTINATION::ATELIER;
    sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_SELECT, 
        resourceManager.Load(ResourceManager::SRC::SE_SELECT).handleId_);
    sound.AdjustVolume(SoundManager::SOUND::SE_SELECT, SE_VOLUME);
}

void TeleportUI::Show(void)
{
    isVisible_ = true;
    Application::GetInstance().SetActiveUIType(Application::ACTIVE_UI_TYPE::TELEPORT);
}

void TeleportUI::Hide(void)
{
    isVisible_ = false;
    Application::GetInstance().SetActiveUIType(Application::ACTIVE_UI_TYPE::NONE);
    PlayerStop::GetInstance().ResumeMovement();
}

bool TeleportUI::IsVisible(void) const
{
    return isVisible_;
}

void TeleportUI::Update(void)
{
    auto& sound = SoundManager::GetInstance();

    if (!isVisible_)
    {
        return;
    }

    PlayerStop::GetInstance().StopMovement();

    auto& input = InputManager::GetInstance();

    if (input.IsTriggerDown(KEY_INPUT_UP))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        int index = static_cast<int>(selected_);
        index = (index - 1 + static_cast<int>(DESTINATION::MAX)) 
            % static_cast<int>(DESTINATION::MAX);
        selected_ = static_cast<DESTINATION>(index);
    }
    else if (input.IsTriggerDown(KEY_INPUT_DOWN))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        int index = static_cast<int>(selected_);
        index = (index + 1) % static_cast<int>(DESTINATION::MAX);
        selected_ = static_cast<DESTINATION>(index);
    }

    if (input.IsTriggerDown(KEY_INPUT_RETURN))
    {
        switch (selected_)
        {
        case DESTINATION::GUILD:
            sound.Play(SoundManager::SOUND::SE_PUSH);
            stageManager_->ChangeStage(StageManager::STAGE_ID::GUILD);
            PlayerStop::GetInstance().ResumeMovement();
            break;

        case DESTINATION::ATELIER:
            sound.Play(SoundManager::SOUND::SE_PUSH);
            stageManager_->ChangeStage(StageManager::STAGE_ID::ATELIER);
            PlayerStop::GetInstance().ResumeMovement();
            break;

        case DESTINATION::GARDEN:
            sound.Play(SoundManager::SOUND::SE_PUSH);
            stageManager_->ChangeStage(StageManager::STAGE_ID::GARDEN);
            PlayerStop::GetInstance().ResumeMovement();
            break;

        case DESTINATION::MAX:
            break;
        }

        Hide();
    }

    if (input.IsTriggerDown(KEY_INPUT_ESCAPE))
    {
        sound.Play(SoundManager::SOUND::SE_CANCEL);
        Hide();
        PlayerStop::GetInstance().ResumeMovement();
    }
}

void TeleportUI::Draw(void)
{
    if (!isVisible_)
    {
        return;
    }

    const char* options[] = { "ギルド", "アトリエ", "ガーデン" };
    const int optionsCount = static_cast<int>(DESTINATION::MAX);

    const int screenWidth = Application::FULL_SCREEN_SIZE_X;
    const int screenHeight = Application::FULL_SCREEN_SIZE_Y;

    int basePositionX = (screenWidth - DRAW_BOX_OFFSET_LEFT) / 2;
    int basePositionY = screenHeight / 4;

    for (int index = 0; index < optionsCount; ++index)
    {
        int drawPositionY = basePositionY + index * (DRAW_BOX_HEIGHT + DRAW_BOX_MARGIN);
        unsigned int color = (index == static_cast<int>(selected_)) ? COLOR_YELLOW : COLOR_WHITE;

        DrawBox(basePositionX - DRAW_BOX_OFFSET_LEFT, drawPositionY, basePositionX
            + DRAW_BOX_OFFSET_RIGHT, drawPositionY + DRAW_BOX_HEIGHT, COLOR_BLACK, true);
        DrawBox(basePositionX - DRAW_BOX_OFFSET_LEFT, drawPositionY, basePositionX
            + DRAW_BOX_OFFSET_RIGHT, drawPositionY + DRAW_BOX_HEIGHT, color, false);

        Font::GetInstance().DrawDefaultText(basePositionX + DRAW_TEXT_OFFSET_X,
            drawPositionY + DRAW_TEXT_OFFSET_Y, options[index], color, FONT_SIZE);
    }
}