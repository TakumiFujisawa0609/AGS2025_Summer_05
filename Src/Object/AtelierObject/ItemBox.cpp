#include "ItemBox.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../DrawUI/SceneUI/InventoryUI.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "../player.h"

ItemBox::ItemBox()
	: isShowUI_(false), isInventoryOpen_(false), inventoryUI_(new InventoryUI())
{
}

ItemBox::~ItemBox()
{
	delete inventoryUI_;
	inventoryUI_ = nullptr;
}

void ItemBox::SetPlayer(std::shared_ptr<Player> player)
{
	player_ = player;
}

void ItemBox::Init(void)
{
	auto& res = ResourceManager::GetInstance();
	trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::BOX));
	trans_.pos = MODEL_POS;
	trans_.scl = SCALE;
	trans_.rot = VGet(0.0f, 0.0f, 0.0f);
	radius_ = RADIUS;

	inventoryUI_->Init();
}

void ItemBox::Update(void)
{
	auto& input = InputManager::GetInstance();

	if (isShowUI_ && !isInventoryOpen_)
	{
		if (input.IsTrgDown(KEY_INPUT_RETURN))
		{
			Application::GetInstance().SetActiveUI(true);
			SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);
			isInventoryOpen_ = true;
			if (inventoryUI_) inventoryUI_->Show(); // ← Zキー制御なしで表示
		}
	}

	if (isInventoryOpen_ && inventoryUI_)
	{
		inventoryUI_->Update();
		if (input.IsTrgDown(KEY_INPUT_ESCAPE))
		{
			Application::GetInstance().SetActiveUI(true);
			SoundManager::GetInstance().Play(SoundManager::SOUND::SE_CANCEL);
			isInventoryOpen_ = false;
			inventoryUI_->Hide();
		}
	}
}
void ItemBox::Draw(void)
{
	// モデル描画
	if (trans_.modelId >= 0)
	{
		MV1SetScale(trans_.modelId, trans_.scl);
		MV1SetPosition(trans_.modelId, trans_.pos);
		MV1SetRotationXYZ(trans_.modelId, trans_.rot);
		MV1DrawModel(trans_.modelId);
	}
}

void ItemBox::DrawUI(void)
{

	const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
	const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

	// UIメッセージ表示（インベントリが未表示のとき）
	if (isShowUI_ && !isInventoryOpen_)
	{
		const char* text = "アイテムボックス";
		int fontSize = 24;
		int textWidth = GetDrawStringWidth(text, strlen(text), fontSize);
		int boxWidth = textWidth + 30;
		int boxHeight = 30;
		int boxX = (screenWidth - boxWidth) / 2;
		int boxY = screenHeight / 2 + 180;

		DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 60, boxY + boxHeight + 10, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 60, boxY + boxHeight + 10, GetColor(255, 255, 255), FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 5, boxY + 5, text, GetColor(255, 255, 255), fontSize);
	}

	// インベントリ表示中
	if (isInventoryOpen_)
	{
		inventoryUI_->Draw();
	}
}

void ItemBox::Release(void)
{
	if (trans_.modelId >= 0)
	{
		MV1DeleteModel(trans_.modelId);
		trans_.modelId = -1;
	}

	delete inventoryUI_;
	inventoryUI_ = nullptr;
}

HitObject::HIT_TYPE ItemBox::GetHitType(void) const
{
	return HIT_TYPE::SPHERE;
}

VECTOR ItemBox::GetHitPosition(void) const
{
	return trans_.pos;
}

float ItemBox::GetHitRadius(void) const
{
	return radius_;
}

void ItemBox::ShowUI(void)
{
	isShowUI_ = true;
}

void ItemBox::HideUI(void)
{
	isShowUI_ = false;
	isInventoryOpen_ = false;
	if (inventoryUI_) inventoryUI_->Hide();
}

bool ItemBox::IsValid(void) const
{
	return true;
}

void ItemBox::OnPlayerHit(void)
{
	ShowUI();
}

void ItemBox::OnPlayerExit(void)
{
	HideUI();
}

bool ItemBox::IsVisible(void) const
{
	return inventoryUI_->IsVisible();
}