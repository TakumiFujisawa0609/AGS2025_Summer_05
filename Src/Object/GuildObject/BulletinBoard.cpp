#include "BulletinBoard.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "./../../DrawUI/SceneUI/QuestUI.h"

BulletinBoard::BulletinBoard(void)
{
	trans_ = Transform();
	trans_.pos = VECTOR();
	trans_.localPos = VAdd(trans_.pos, MODEL_POS);
	radius_ = 0.0f;
	speed_ = 0.0f;
	isShowUI_ = false;
	isShowQuestList_ = false;
	selectedQuest_ = 0;
}

BulletinBoard::~BulletinBoard(void)
{

}

void BulletinBoard::Init(void)
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
	isShowQuestList_ = false;
	selectedQuest_ = 0;

	// 依頼リストを初期化
	questList_[0] = "依頼1: 回復ポーソンを3こ納品";
	questList_[1] = "依頼2: 解毒ポーソンを2こ納品";
	questList_[2] = "依頼3: 魔法ポーソンを1こ納品";

	//モデル制御
	trans_.Update();

}

void BulletinBoard::Update(void)
{
	auto& input = InputManager::GetInstance();

	trans_.Update();
	// エンターキーが押された時の処理
	if (isShowUI_ && input.IsTrgDown(KEY_INPUT_RETURN))
	{
		if (!isShowQuestList_)
		{
			isShowQuestList_ = true;
		}
		else
		{
			// 依頼選択の確定処理
			auto& questUI = QuestUI::GetInstance();
			questUI.AcceptQuest(selectedQuest_);

			// 依頼受注後はUIを閉じる
			isShowQuestList_ = false;
			isShowUI_ = false;
		}
	}

	// 依頼リスト表示中の選択処理
	if (isShowQuestList_)
	{
		// 上下キーで選択を変更
		if (input.IsTrgDown(KEY_INPUT_UP))
		{
			selectedQuest_ = (selectedQuest_ - 1 + 3) % 3;
		}
		else if (input.IsTrgDown(KEY_INPUT_DOWN))
		{
			selectedQuest_ = (selectedQuest_ + 1) % 3;
		}

		// ESCキーで依頼リストを閉じる
		if (input.IsTrgDown(KEY_INPUT_X))
		{
			isShowQuestList_ = false;
		}
	}
}

void BulletinBoard::Draw(void)
{

	MV1DrawModel(trans_.modelId);

	if (isShowUI_)
	{
		if (!isShowQuestList_)
		{
			// 基本UI表示
			DrawBox(200, 200, 600, 280, GetColor(0, 0, 0), TRUE);
			DrawBox(200, 200, 600, 280, GetColor(255, 255, 255), FALSE);
			Font::GetInstance().DrawDefaultText(220, 230, "掲示板 - Enterキーで納品依頼一覧を表示", 0xffffff, 24);
		}
		else
		{
			// 依頼リスト表示
			DrawBox(150, 150, 650, 400, GetColor(0, 0, 0), TRUE);
			DrawBox(150, 150, 650, 400, GetColor(255, 255, 255), FALSE);

			// タイトル表示
			Font::GetInstance().DrawDefaultText(170, 170, "===== 納品依頼一覧 =====", 0xffffff, 24);

			// 依頼リスト表示
			for (int i = 0; i < 3; i++)
			{
				int color = (i == selectedQuest_) ? 0xff00ff : 0xffffff; // 選択中の依頼をピンク色で表示
				int yPos = 200 + (i * 30);

				// 選択カーソル表示
				if (i == selectedQuest_)
				{
					Font::GetInstance().DrawDefaultText(170, yPos, "→", 0xff00ff, 24);
				}

				Font::GetInstance().DrawDefaultText(200, yPos, questList_[i].c_str(), color, 20);
			}

			// 操作説明
			Font::GetInstance().DrawDefaultText(170, 320, "↑↓キー: 選択  Enter: 決定  ESC: 戻る", 0xcccccc, 16);
		}
	}

	DrawSphere3D(trans_.pos, radius_, 16, 0xffffff, 0xffffff, false);
	DrawFormatString(0, 80, 0xffffff, "表示判定 : %d", isShowUI_);
	DrawFormatString(0, 100, 0xffffff, "依頼リスト表示 : %d", isShowQuestList_);
	DrawFormatString(0, 120, 0xffffff, "選択中の依頼 : %d", selectedQuest_);
}

void BulletinBoard::Release(void)
{

}

VECTOR BulletinBoard::GetHitPosition() const
{
	return trans_.pos;
}

float BulletinBoard::GetHitRadius() const
{
	return radius_;
}

void BulletinBoard::ShowUI(void)
{
 	isShowUI_ = true;
	isShowQuestList_ = false;
}

void BulletinBoard::HideUI(void)
{
	isShowUI_ = false;
	isShowQuestList_ = false;
}

bool BulletinBoard::IsValid(void) const
{
	return true;
}
