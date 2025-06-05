#include "BulletinBoard.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "../../DrawUI/SceneUI/QuestUI.h"

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

#ifdef _DEBUG
	const int screenWidth = Application::SCREEN_SIZE_X;
	const int screenHeight = Application::SCREEN_SIZE_Y;
#else
	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SIZE_X;

#endif // _DEBUG

	

	if (isShowUI_)
	{ 
		if (!isShowQuestList_)
		{
			// テキスト内容
			const char* text = "依頼";
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
		else
		{
			// 依頼リストのボックスサイズ
			const int boxWidth = 600;
			const int boxHeight = 300;
			const int boxX = (screenWidth - boxWidth) / 2;
			const int boxY = 150;

			DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(0, 0, 0), TRUE);
			DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(255, 255, 255), FALSE);

			// タイトル
			Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 20, "===== 納品依頼一覧 =====", 0xffffff, 24);

			// 依頼リスト描画
			for (int i = 0; i < 3; i++)
			{
				int color = (i == selectedQuest_) ? 0xff00ff : 0xffffff;
				int yPos = boxY + 60 + (i * 30);

				if (i == selectedQuest_)
				{
					Font::GetInstance().DrawDefaultText(boxX + 20, yPos, "→", 0xff00ff, 24);
				}

				Font::GetInstance().DrawDefaultText(boxX + 50, yPos, questList_[i].c_str(), color, 20);
			}

			// 操作説明
			Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 230, "↑↓キー: 選択  Enter: 決定  X: 戻る", 0xcccccc, 16);
		}
	}

	//DrawSphere3D(trans_.pos, radius_, 16, 0xffffff, 0xffffff, false);
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
