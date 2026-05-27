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
	: stageManager_(stageManager),player_(player), isVisible_(false), selected_(DESTINATION::ATELIER)
{
}

void TeleportUI::Init(void)
{
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	selected_ = DESTINATION::ATELIER;
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_SELECT, res.Load(ResourceManager::SRC::SE_SELECT).handleId_);
	sound.AdjustVolume(SoundManager::SOUND::SE_SELECT, 50);
}

void TeleportUI::Show(void)
{
	isVisible_ = true;
	Application::GetInstance().SetsActiveUI(ActiveUI::TELEPORT);
}

void TeleportUI::Hide(void)
{
	isVisible_ = false;
	Application::GetInstance().SetsActiveUI(ActiveUI::NONE);
	PlayerStop::GetInstance().ResumeMovement();
}

bool TeleportUI::IsVisible(void) const
{
	return isVisible_;
}

void TeleportUI::Update(void)
{
	auto& sound = SoundManager::GetInstance();
	if (!isVisible_) return;

	PlayerStop::GetInstance().StopMovement();

	auto& input = InputManager::GetInstance();

	if (input.IsTrgDown(KEY_INPUT_UP))
	{
		sound.Play(SoundManager::SOUND::SE_SELECT);
		int idx = static_cast<int>(selected_);
		idx = (idx - 1 + static_cast<int>(DESTINATION::MAX)) % static_cast<int>(DESTINATION::MAX);
		selected_ = static_cast<DESTINATION>(idx);
	}
	else if (input.IsTrgDown(KEY_INPUT_DOWN))
	{
		sound.Play(SoundManager::SOUND::SE_SELECT);
		int idx = static_cast<int>(selected_);
		idx = (idx + 1) % static_cast<int>(DESTINATION::MAX);
		selected_ = static_cast<DESTINATION>(idx);
	}

	if (input.IsTrgDown(KEY_INPUT_RETURN))
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

		}
		Hide();  // UIを閉じる
	}

	if (input.IsTrgDown(KEY_INPUT_ESCAPE))
	{
		sound.Play(SoundManager::SOUND::SE_CANCEL);
		Hide();
		PlayerStop::GetInstance().ResumeMovement();
	}
}

void TeleportUI::Draw(void)
{
	if (!isVisible_) return;

	const char* options[] = { "ギルド", "アトリエ", "ガーデン" };
	const int count = static_cast<int>(DESTINATION::MAX);

	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

	int fontSize = 24;
	int boxX = (screenWidth - 200) / 2;
	int boxY = screenHeight / 4;

	for (int i = 0; i < count; ++i)
	{
		int boxHeight = 32;
		int y = boxY + i * (boxHeight + 8);
		int color = (i == static_cast<int>(selected_)) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);

		DrawBox(boxX - 200, y, boxX + 400, y + boxHeight, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX -200, y, boxX + 400, y + boxHeight, color, FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 80, y + 4, options[i], color, fontSize);
	}
}
