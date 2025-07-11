#include "Teleport.h"

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

Teleport::Teleport(StageManager* stageManager) : stageManager_(stageManager)
{
	isShowUI_ = false;
}

Teleport::~Teleport(void)
{

}

void Teleport::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//モデル
	trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::BULLETIN_BOARD));
	trans_.scl = SCALE;
	radius_ = RADIUS;
	speed_ = 0.0f;
	isShowUI_ = false;
	trans_.pos = MODEL_POS;

	teleportUI_ = std::make_unique<TeleportUI>(stageManager_, stageManager_->GetPlayer().get());
	teleportUI_->Init();

}

void Teleport::Update(void)
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
			teleportUI_->Show();  // UI表示開始
			isShowUI_ = false;
		}
	}
}

void Teleport::Draw(void)
{
	MV1DrawModel(trans_.modelId);

	if (isShowUI_)
	{
		const char* text = "移動";
		int fontSize = 14;
		int textWidth = GetDrawStringWidth(text, strlen(text), -1);
		int boxWidth = textWidth + 30;
		int boxHeight = 20;
		int boxX = (Application::DEFA_SCREEN_SIZE_X - boxWidth) / 2;
		int boxY = (Application::DEFA_SCREEN_SZIE_Y / 4) + boxHeight;

		DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(255, 255, 255), FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 5, text, 0xffffff, fontSize);
	}

	if (teleportUI_)
	{
		teleportUI_->Draw();
	}
}

void Teleport::Release(void)
{
}

HitObject::HIT_TYPE Teleport::GetHitType(void) const
{
	return HIT_TYPE::SPHERE;
}

VECTOR Teleport::GetHitPosition(void) const
{
	return trans_.pos;
}

float Teleport::GetHitRadius(void) const
{
	return radius_;
}

void Teleport::ShowUI(void)
{
	isShowUI_ = true;
}

void Teleport::HideUI(void)
{
	isShowUI_ = false;
}

bool Teleport::IsValid(void) const
{
	return true;
}

void Teleport::OnPlayerHit(void)
{
	ShowUI();
}

void Teleport::OnPlayerExit(void)
{
	HideUI();
}
