#include "BulletinBoard.h"

#include "../../Manager/Generic/ResourceManager.h"
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
	imageBoardId_ = 0;

	uiOpenWaitFrame_ = 0;

	uiShowUIDelayFrames_ = 0;
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

	//掲示板の画像
	imageBoardId_ = res.Load(ResourceManager::SRC::IMAGE_BOARD).handleId_;

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
			isShowUI_ = false;
		}
	}
}

void BulletinBoard::Draw(void)
{
	MV1DrawModel(trans_.modelId);

	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

	if (isShowUI_)
	{
		auto& questUI = QuestUI::GetInstance();
		const auto& quests = questUI.GetSelectedQuests();

		if (!isShowQuestList_)
		{
			// 「依頼」という表示だけ
			const char* text = "依頼";
			int fontSize = 14;
			int textWidth = GetDrawStringWidth(text, strlen(text), -1);
			int boxWidth = textWidth + 30;
			int boxHeight = 20;
			int boxX = (screenWidth - boxWidth) / 2;
			int boxY = (screenHeight / 4) + boxHeight;

			DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(0, 0, 0), TRUE);
			DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(255, 255, 255), FALSE);
			Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 5, text, 0xffffff, fontSize);
		}
		else
		{
			// 依頼ボックスの設定
			const int boxWidth = 150;
			const int boxHeight = 300;
			const int spacing = 40;
			const int startX = (screenWidth - (3 * boxWidth + 2 * spacing)) / 2;
			const int startY = 180;

			DrawRotaGraph3(0, 0, 0, 0, 0.98f, 0.98f, 0, imageBoardId_, TRUE);

			Font::GetInstance().DrawDefaultText(startX, startY - 100, "===== 納品依頼一覧 =====", 0xffffff, 24);

			for (int i = 0; i < 3; i++)
			{
				int xPos = startX + i * (boxWidth + spacing);
				int boxColor = (i == selectedQuest_) ? GetColor(50, 50, 80) : GetColor(0, 0, 0);
				int borderColor = (i == selectedQuest_) ? GetColor(255, 0, 255) : GetColor(255, 255, 255);
				int textColor = (i == selectedQuest_) ? 0xff00ff : 0xffffff;

				DrawBox(xPos, startY, xPos + boxWidth, startY + boxHeight, boxColor, TRUE);
				DrawBox(xPos, startY, xPos + boxWidth, startY + boxHeight, borderColor, FALSE);

				std::string questText = "未設定";
				if (i < (int)quests.size())
				{
					const auto& quest = quests[i];
					questText = quest.title + " x" + std::to_string(quest.requiredAmount);
				}

				Font::GetInstance().DrawDefaultText(xPos + 10, startY + boxHeight / 2 - 10,
					questText.c_str(), textColor, 18);
			}

			Font::GetInstance().DrawDefaultText(startX, startY + boxHeight + 30,
				"←→キー: 選択  Enter: 決定  X: 戻る", 0xcccccc, 16);
		}
	}
}



void BulletinBoard::Release(void)
{

}

VECTOR BulletinBoard::GetHitMin(void) const
{
	return { trans_.pos.x - radius_, trans_.pos.y - radius_, trans_.pos.z - radius_ };
}

VECTOR BulletinBoard::GetHitMax(void) const
{
	return { trans_.pos.x + radius_, trans_.pos.y + radius_, trans_.pos.z + radius_ };
}

HitObject::HIT_TYPE BulletinBoard::GetHitType(void) const
{
	return HIT_TYPE::SPHERE;
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
	uiOpenWaitFrame_ = UI_ENTER_DELAY_FRAME;
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

void BulletinBoard::OnPlayerHit(void)
{
	ShowUI();
}

void BulletinBoard::OnPlayerExit(void)
{
	HideUI();
}

void BulletinBoard::UpdateUIVisibility(bool isHit)
{
	// UIがすでに表示中で、プレイヤーが離れていなければ何もしない
	if (isShowUI_)
	{
		// UIを維持しつつ、非表示用のカウントは止める
		uiVisible_ = true;
		uiHideDelayFrames_ = UI_HIDE_DELAY_MAX;
		return;
	}

	// UIが未表示時のみ、接触中ならUIを出す
	if (isHit)
	{
		uiVisible_ = true;
		uiHideDelayFrames_ = UI_HIDE_DELAY_MAX;
		ShowUI();
	}
	else
	{
		if (uiHideDelayFrames_ > 0)
		{
			uiHideDelayFrames_--;
			ShowUI();
		}
		else if (uiVisible_)
		{
			uiVisible_ = false;
			HideUI();
			OnPlayerExit();
		}
	}
}
