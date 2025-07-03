#include "AlchemyPot.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
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

	//モデル
	trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::BULLETIN_BOARD));
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal = Quaternion::AngleAxis(Utility::Deg2RadF(180.0f), Utility::AXIS_Y);
	trans_.scl = SCALE;
	radius_ = RADIUS;
	speed_ = 0.0f;
	isShowUI_ = false;
	trans_.pos = MODEL_POS;
}

void AlchemyPot::Update(void)
{
	auto& input = InputManager::GetInstance();
	auto& alchemy = AlchemyManager::GetInstance();

	trans_.Update();

	bool start = false;

	// エンターキーが押された時の処理
	if (isShowUI_ && input.IsTrgDown(KEY_INPUT_RETURN))
	{
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

	MV1DrawModel(trans_.modelId);

	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SIZE_X;

	

	if (alchemy.IsOpen())
	{
		alchemy.Draw();
	}

	if (isShowUI_)
	{
		// テキスト内容
		const char* text = "錬金";
		int fontSize = 18;
		int textWidth = GetDrawStringWidth(text, strlen(text), -1);
		int boxWidth = textWidth + 30; // 余白を加える
		int boxHeight = 30;

		int boxX = (screenWidth - boxWidth) / 2;
		int boxY = boxY = (screenHeight / 4) + 150;

		// UI表示（中央）
		DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(255, 255, 255), FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 15, boxY + 5, text, 0xffffff, fontSize);
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
