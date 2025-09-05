#include "AlchemyPot.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../Object/Manager/AlchemyManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "../player.h"


AlchemyPot::AlchemyPot(void)
{
	isShowUI_ = false;
	
}

AlchemyPot::~AlchemyPot(void)
{
}

void AlchemyPot::SetPlayer(std::shared_ptr<Player> player)
{
	player_ = player;
}

void AlchemyPot::Init(void)
{
	auto& res = ResourceManager::GetInstance();
	trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::ALCHEMYPOT));
	radius_ = RADIUS;
	isShowUI_ = false;

	trans_.pos = MODEL_POS;
	trans_.scl = SCALE;
	trans_.rot = { 0.0f, 0.0f, 0.0f };


	
}

void AlchemyPot::Update(void)
{
	auto& input = InputManager::GetInstance();
	auto& alchemy = AlchemyManager::GetInstance();

	bool start = false;

	// エンターキーが押された時の処理
	if (isShowUI_ && input.IsTrgDown(KEY_INPUT_RETURN))
	{
		Application::GetInstance().SetActiveUI(true);
		SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);
		// 錬金メニューが閉じている時のみ開く
		if (!alchemy.IsOpen())
		{
			alchemy.Open();
		}
		
	}

	// 錬金メニューが開いているときのみ更新
	if (alchemy.IsOpen())
	{
		alchemy.Update();
		isShowUI_ = false;
	}
}

void AlchemyPot::Draw(void)
{
	auto& alchemy = AlchemyManager::GetInstance();

	if (trans_.modelId >= 0)
	{
		MV1SetScale(trans_.modelId, trans_.scl);
		MV1SetPosition(trans_.modelId, trans_.pos);
		MV1SetRotationXYZ(trans_.modelId, trans_.rot);
		MV1DrawModel(trans_.modelId);
	}

	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

	

	if (alchemy.IsOpen())
	{
		alchemy.Draw();
	}

	if (isShowUI_)
	{
		// テキスト内容
		const char* text = "錬金";
		int fontSize = 24;
		int textWidth = GetDrawStringWidth(text, strlen(text), fontSize);
		int boxWidth = textWidth + 30;
		int boxHeight = 30;

		int boxX = (screenWidth - boxWidth) / 2;
		int boxY = screenHeight / 2 + 100;

		// UI表示（中央）
		DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(255, 255, 255), FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 5, boxY + 5, text, GetColor(255, 255, 255), fontSize);
	}
}

void AlchemyPot::Release(void)
{
}

HitObject::HIT_TYPE AlchemyPot::GetHitType(void) const
{
	return HIT_TYPE::SPHERE;
}

VECTOR AlchemyPot::GetHitPosition(void) const
{
	return trans_.pos;
}

float AlchemyPot::GetHitRadius(void) const
{
	return radius_;
}

void AlchemyPot::ShowUI(void)
{
	isShowUI_ = true;
}

void AlchemyPot::HideUI(void)
{
	isShowUI_ = false;
	AlchemyManager::GetInstance().Close();
}

bool AlchemyPot::IsValid(void) const
{
	return true;
}

void AlchemyPot::OnPlayerHit(void)  
{  
   ShowUI();  
   VECTOR playerPos = player_->GetPos();
}

void AlchemyPot::OnPlayerExit(void)
{
	HideUI();
}

bool AlchemyPot::isOpen(void) const
{
	return AlchemyManager::GetInstance().IsOpen();
}
