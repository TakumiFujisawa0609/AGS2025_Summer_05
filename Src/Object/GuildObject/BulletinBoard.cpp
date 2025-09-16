#include "BulletinBoard.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "../../DrawUI/SceneUI/QuestUI.h"
#include "../PlayerStop.h"

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

	imageQuest_ = 0;

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
	trans_.rot = { 0.0f, -105.3f, 0.0f };
	trans_.pos = MODEL_POS;
	radius_ = RADIUS;
	speed_ = 0.0f;
	isShowUI_ = false;
	isShowQuestList_ = false;
	selectedQuest_ = 0;

	//掲示板の画像
	imageBoardId_ = res.Load(ResourceManager::SRC::IMAGE_BOARD).handleId_;

	imageQuest_ = res.Load(ResourceManager::SRC::IMAGE_REQUEST).handleId_;

	MV1SetScale(trans_.modelId, trans_.scl);
	MV1SetPosition(trans_.modelId, trans_.pos);
	MV1SetRotationXYZ(trans_.modelId, trans_.rot);

}

void BulletinBoard::Update(void)
{
	auto& input = InputManager::GetInstance();
	auto& sound = SoundManager::GetInstance();
	auto& app = Application::GetInstance();

	// エンターキーが押された時の処理
	if (isShowUI_ && input.IsTrgDown(KEY_INPUT_RETURN))
	{
		// --- UI優先度を QUEST に設定 ---
		app.SetsActiveUI(ActiveUI::QUEST);
		app.SetActiveUI(true);

		sound.Play(SoundManager::SOUND::SE_PUSH);

		if (!isShowQuestList_)
		{
			isShowQuestList_ = true;
		}
		else
		{
			auto& questUI = QuestUI::GetInstance();
			const auto& selectedQuests = questUI.GetSelectedQuests();

			if (selectedQuest_ >= 0 && selectedQuest_ < (int)selectedQuests.size())
			{
				int questId = selectedQuests[selectedQuest_].id;
				questUI.AcceptQuest(questId);
			}

			PlayerStop::GetInstance().ResumeMovement();
			isShowQuestList_ = false;
			isShowUI_ = false;

			// --- UI閉じたら優先度を解除 ---
			app.SetsActiveUI(ActiveUI::NONE);
			app.SetActiveUI(false);
		}
	}

	// 依頼リスト表示中の選択処理
	if (isShowQuestList_)
	{
		if (input.IsTrgDown(KEY_INPUT_LEFT))
		{
			sound.Play(SoundManager::SOUND::SE_SELECT);
			selectedQuest_ = (selectedQuest_ - 1 + 3) % 3;
		}
		else if (input.IsTrgDown(KEY_INPUT_RIGHT))
		{
			sound.Play(SoundManager::SOUND::SE_SELECT);
			selectedQuest_ = (selectedQuest_ + 1) % 3;
		}

		if (input.IsTrgDown(KEY_INPUT_ESCAPE))
		{
			sound.Play(SoundManager::SOUND::SE_CANCEL);
			isShowQuestList_ = false;
			isShowUI_ = false;
			PlayerStop::GetInstance().ResumeMovement();

			// --- ESCで閉じるときも優先度解除 ---
			app.SetsActiveUI(ActiveUI::NONE);
			app.SetActiveUI(false);
		}
	}

	if (!selectedQuest_)
	{
		PlayerStop::GetInstance().ResumeMovement();
	}
}

void BulletinBoard::DrawModel(void)
{
	// 3Dモデル描画（Zバッファ有効）
	MV1DrawModel(trans_.modelId);
}

void BulletinBoard::DrawUI(void)
{
	// Zバッファ無効化してUIを描画
	SetUseZBufferFlag(FALSE);

	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

	if (!isShowUI_) {
		// UI非表示ならここで終わり
		SetUseZBufferFlag(TRUE);
		return;
	}

	auto& questUI = QuestUI::GetInstance();
	const auto& quests = questUI.GetSelectedQuests();

	if (!isShowQuestList_)
	{
		const char* text = "依頼";
		int fontSize = 24;
		int textWidth = GetDrawStringWidth(text, strlen(text), fontSize);
		int boxWidth = textWidth + 30;
		int boxHeight = 30;
		int boxX = (screenWidth - boxWidth) / 2;
		int boxY = screenHeight / 2 + 100;

		DrawBox(boxX - 20, boxY-10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX - 20, boxY-10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(255, 255, 255), FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 5, boxY + 5, text, GetColor(255, 255, 255), fontSize);
	}
	else
	{
		PlayerStop::GetInstance().StopMovement();

		uiOpenWaitFrame_ = UI_ENTER_DELAY_FRAME;
		// 依頼ボックスの設定
		const int boxWidth = 400;
		const int boxHeight = 600;
		const int spacing = 100;
		const int startX = (screenWidth - (3 * boxWidth + 2 * spacing)) / 2;
		const int startY = 200;

		DrawRotaGraph3(-5, -5, 0, 0, 1.23f, 1.23f, 0, imageBoardId_, TRUE);

		Font::GetInstance().DrawDefaultText(startX, startY - 100, "===== 納品依頼一覧 =====", 0xffffff, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);

		for (int i = 0; i < 3; i++)
		{
			int xPos = startX + i * (boxWidth + spacing);
			int boxColor = (i == selectedQuest_) ? GetColor(50, 50, 80) : GetColor(0, 0, 0);
			int borderColor = (i == selectedQuest_) ? GetColor(255, 0, 255) : GetColor(255, 255, 255);
			int textColor = (i == selectedQuest_) ? 0xffff00 : 0xffffff;

			int imgW, imgH;
			GetGraphSize(imageQuest_, &imgW, &imgH);

			int imgX = xPos + (boxWidth / 2) - (imgW / 2);
			int imgY = startY + (boxHeight / 2) - (imgH / 2);

			DrawGraph(imgX, imgY, imageQuest_, TRUE);

			//DrawBox(xPos, startY, xPos + boxWidth, startY + boxHeight, boxColor, TRUE);
			//DrawBox(xPos, startY, xPos + boxWidth, startY + boxHeight, borderColor, FALSE);
			
			std::string questText = "未設定";
			if (i < (int)quests.size())
			{
				const auto& quest = quests[i];
				questText = quest.title + " x" + std::to_string(quest.requiredAmount);
			}

			Font::GetInstance().DrawDefaultText(xPos + 10, startY + boxHeight / 2 - 10,
				questText.c_str(), textColor, 32);
		}

		Font::GetInstance().DrawDefaultText(startX, startY + boxHeight + 30,
			"←→キー: 選択  Enter: 決定  ESC: 閉じる", 0xcccccc, 24);
	}

	// UI描画終了後はZバッファを元に戻す
	SetUseZBufferFlag(TRUE);
}

void BulletinBoard::Draw(void)
{
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

bool BulletinBoard::GetQuestList(void) const
{
	return isShowQuestList_;
}
