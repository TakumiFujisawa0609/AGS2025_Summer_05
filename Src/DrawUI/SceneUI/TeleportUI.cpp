#include "TeleportUI.h"

#include <DxLib.h>
#include <cstring>
#include "../../Application.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../DrawUI/Font.h"
#include "../../Object/Manager/StageManager.h"
#include "../../Object/PlayerStop.h"
#include "../../Object/player.h"

TeleportUI::TeleportUI(StageManager* stageManager, Player* player)
	: stageManager_(stageManager),player_(player), isVisible_(false), selected_(DESTINATION::ATELIER)
{
}

void TeleportUI::Init(void)
{
	selected_ = DESTINATION::ATELIER;
}

void TeleportUI::Show(void)
{
	isVisible_ = true;
}

void TeleportUI::Hide(void)
{
	isVisible_ = false;
	PlayerStop::GetInstance().ResumeMovement();
}

bool TeleportUI::IsVisible(void) const
{
	return isVisible_;
}

void TeleportUI::Update(void)
{
	if (!isVisible_) return;
	PlayerStop::GetInstance().StopMovement();

	auto& input = InputManager::GetInstance();

	if (input.IsTrgDown(KEY_INPUT_UP))
	{
		int idx = static_cast<int>(selected_);
		idx = (idx - 1 + static_cast<int>(DESTINATION::MAX)) % static_cast<int>(DESTINATION::MAX);
		selected_ = static_cast<DESTINATION>(idx);
	}
	else if (input.IsTrgDown(KEY_INPUT_DOWN))
	{
		int idx = static_cast<int>(selected_);
		idx = (idx + 1) % static_cast<int>(DESTINATION::MAX);
		selected_ = static_cast<DESTINATION>(idx);
	}

	if (input.IsTrgDown(KEY_INPUT_RETURN))
	{
		VECTOR teleportPos = { 0, 0, 0 };
		switch (selected_)
		{
		case DESTINATION::GUILD:
			stageManager_->ChangeStage(StageManager::STAGE_ID::GUILD);
			teleportPos = { 0, 10, -30 };
			break;
		case DESTINATION::ATELIER:
			stageManager_->ChangeStage(StageManager::STAGE_ID::ATELIER);
			teleportPos = { 0, 10, -30 };
			break;
		case DESTINATION::GARDEN:
			stageManager_->ChangeStage(StageManager::STAGE_ID::GARDEN);
			teleportPos = { 0, 10, -30 };
			break;
		}
		if (player_)
		{
			player_->SetPos(teleportPos);
		}
		Hide();  // UIを閉じる
	}

	if (input.IsTrgDown(KEY_INPUT_ESCAPE))
	{
		Hide();
	}
}

void TeleportUI::Draw(void)
{
	if (!isVisible_) return;

	const char* options[] = { "ギルド", "アトリエ", "庭" };
	const int count = static_cast<int>(DESTINATION::MAX);

	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

	int fontSize = 14;
	int boxX = (screenWidth - 200) / 2;
	int boxY = screenHeight / 4;

	for (int i = 0; i < count; ++i)
	{
		int boxHeight = 24;
		int y = boxY + i * (boxHeight + 8);
		int color = (i == static_cast<int>(selected_)) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);

		DrawBox(boxX, y, boxX + 200, y + boxHeight, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX, y, boxX + 200, y + boxHeight, color, FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 10, y + 4, options[i], color, fontSize);
	}
}
