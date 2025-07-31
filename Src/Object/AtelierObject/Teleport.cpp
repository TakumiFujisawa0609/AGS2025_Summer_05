#include "Teleport.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Decoration/SoundManager.h"
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
			SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);
			teleportUI_->Show();  // UI表示開始
			isShowUI_ = false;
		}
	}
}

void Teleport::Draw(void)
{
	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

	if (isShowUI_)
	{
		const char* text = "移動";
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
