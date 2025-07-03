#include "warp.h"

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

Warp::Warp(StageManager* stageManager) : stageManager_(stageManager)
{
	isShowUI_ = false;
}

Warp::~Warp(void)
{

}

void Warp::Init(void)
{
	auto& res = ResourceManager::GetInstance();

	//モデル
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

void Warp::Update(void)
{
	auto& input = InputManager::GetInstance();
	trans_.Update();

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

void Warp::Draw(void)
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

void Warp::Release(void)
{
}

HitObject::HIT_TYPE Warp::GetHitType(void) const
{
	return HIT_TYPE::SPHERE;
}

VECTOR Warp::GetHitPosition(void) const
{
	return trans_.pos;
}

float Warp::GetHitRadius(void) const
{
	return radius_;
}

void Warp::ShowUI(void)
{
	isShowUI_ = true;
}

void Warp::HideUI(void)
{
	isShowUI_ = false;
}

bool Warp::IsValid(void) const
{
	return true;
}

void Warp::OnPlayerHit(void)
{
	ShowUI();
}

void Warp::OnPlayerExit(void)
{
	HideUI();
}

