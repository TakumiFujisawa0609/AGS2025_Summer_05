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
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal = Quaternion::AngleAxis(Utility::Deg2RadF(180.0f), Utility::AXIS_Y);
	trans_.scl = SCALE;
	radius_ = RADIUS;
	speed_ = 0.0f;
	isShowUI_ = false;
	trans_.pos = MODEL_POS;
}

void Teleport::Update(void)
{
	auto& input = InputManager::GetInstance();

	trans_.Update();

	// エンターキーが押された時の処理
	if (isShowUI_ && input.IsTrgDown(KEY_INPUT_RETURN))
	{
		//ステージ遷移
		if (stageManager_)
		{
			stageManager_->ChangeStage(StageManager::STAGE_ID::GUILD);
		}
	}
}

void Teleport::Draw(void)
{
	MV1DrawModel(trans_.modelId);

	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SIZE_X;

	if (isShowUI_)
	{
		// テキスト内容
		const char* text = "移動";
		int fontSize = 14;
		int textWidth = GetDrawStringWidth(text, strlen(text), -1);
		int boxWidth = textWidth + 30; // 余白を加える
		int boxHeight = 20;

		int boxX = (screenWidth - boxWidth) / 2;
		int boxY = boxY = (screenHeight / 4) + boxHeight;

		// UI表示（中央）
		DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(255, 255, 255), FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 5, text, 0xffffff, fontSize);
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
