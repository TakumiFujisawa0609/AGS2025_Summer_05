#include "TeleportMovement.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../Object/Manager/AlchemyManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include"../../Object/Manager/StageManager.h"
#include "../../DrawUI/SceneUI/TeleportUI.h"


TeleportMovement::TeleportMovement(StageManager* stageManager) : stageManager_(stageManager)
{
	isShowUI_ = false;
}

TeleportMovement::~TeleportMovement(void)
{

}

void TeleportMovement::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//ƒ‚ƒfƒ‹
	trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::BULLETIN_BOARD));
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal = Quaternion::AngleAxis(Utility::Deg2RadF(180.0f), Utility::AXIS_Y);
	trans_.scl = SCALE;
	radius_ = RADIUS;
	speed_ = 0.0f;
	isShowUI_ = false;
	trans_.pos = MODEL_POS;

	teleportUI_ = std::make_unique<TeleportUI>(stageManager_, stageManager_->GetPlayer().get());
	teleportUI_->Init();
}

void TeleportMovement::Update(void)
{
	auto& input = InputManager::GetInstance();

	if (teleportUI_)
	{
		teleportUI_->Update();
	}

	if (isShowUI_ && input.IsTrgDown(KEY_INPUT_RETURN))
	{
		if (teleportUI_)
		{
			Application::GetInstance().SetsActiveUI(ActiveUI::TELEPORT);
			teleportUI_->Show();  // UIŒÄ‚Ño‚µ
		}
	}
}

void TeleportMovement::Draw(void)
{
	MV1DrawModel(trans_.modelId);

	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

	if (isShowUI_)
	{
		const char* text = "ˆÚ“®";
		int fontSize = 24;
		int textWidth = GetDrawStringWidth(text, strlen(text), fontSize);
		int boxWidth = textWidth + 30;
		int boxHeight = 30;
		int boxX = (screenWidth - boxWidth) / 2;
		int boxY = screenHeight / 2 + 100;

		DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(255, 255, 255), FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 5, boxY + 5, text, GetColor(255, 255, 255), fontSize);
	}

	if (teleportUI_)
	{
		teleportUI_->Draw();
	}
}

void TeleportMovement::Release(void)
{
}

HitObject::HIT_TYPE TeleportMovement::GetHitType(void) const
{
	return HIT_TYPE::SPHERE;
}

VECTOR TeleportMovement::GetHitPosition(void) const
{
	return trans_.pos;
}

float TeleportMovement::GetHitRadius(void) const
{
	return radius_;
}

void TeleportMovement::ShowUI(void)
{
	isShowUI_ = true;
}

void TeleportMovement::HideUI(void)
{
	isShowUI_ = false;
	if (teleportUI_) teleportUI_->Hide();
}


bool TeleportMovement::IsValid(void) const
{
	return true;
}

void TeleportMovement::OnPlayerHit(void)
{
	ShowUI();
}

void TeleportMovement::OnPlayerExit(void)
{
	HideUI();
}
