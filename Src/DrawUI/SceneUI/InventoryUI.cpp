#define NOMINMAX
#include "InventoryUI.h"

#include <DxLib.h>
#include <functional>
#include <algorithm>

#include "../../Manager/Generic/InputManager.h"
#include "../../Object/Manager/ItemManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"

InventoryUI::InventoryUI(void)
	: isVisible_(false)
	, selectedItemIndex_(-1)
	, currentTab_(TAB::Material) // 初期は素材タブ
	, frameCount_(0)
{
}

InventoryUI::~InventoryUI(void)
{
}

void InventoryUI::Init(void)
{
	isVisible_ = false;
	selectedItemIndex_ = -1;
	currentTab_ = TAB::Material; // 初期タブは素材
	frameCount_ = 0;
}

void InventoryUI::Show(void)
{
	isVisible_ = true;
	selectedItemIndex_ = 0;
	currentTab_ = TAB::Material;
}

void InventoryUI::Hide(void)
{
	isVisible_ = false;
}


void InventoryUI::Update(void)
{
	auto& input = InputManager::GetInstance();
	auto& itemManager = ItemManager::GetInstance();
	auto& sound = SoundManager::GetInstance();

	if (!isVisible_) return;

	frameCount_++;

	// タブ切り替え（TABキーで切り替え）
	if (input.IsTrgDown(KEY_INPUT_TAB))
	{
		sound.Play(SoundManager::SOUND::SE_PUSH);
		currentTab_ = (currentTab_ == TAB::Material) ? TAB::Product : TAB::Material;
		selectedItemIndex_ = 0;
	}

	int itemCount = (currentTab_ == TAB::Material)
		? itemManager.GetMaterialItemCount()
		: itemManager.GetProductItemCount();

	// 選択が範囲外なら修正
	selectedItemIndex_ = std::clamp(selectedItemIndex_, 0, std::max(0, itemCount - 1));

	int row = selectedItemIndex_ / MAX_COLUMNS;
	int col = selectedItemIndex_ % MAX_COLUMNS;

	if (input.IsTrgDown(KEY_INPUT_UP))
	{
		sound.Play(SoundManager::SOUND::SE_SELECT);
		int newRow = row - 1;
		if (newRow >= 0)
		{
			int newIndex = newRow * MAX_COLUMNS + col;
			if (newIndex < itemCount) selectedItemIndex_ = newIndex;
		}
	}
	if (input.IsTrgDown(KEY_INPUT_DOWN))
	{
		sound.Play(SoundManager::SOUND::SE_SELECT);
		int newRow = row + 1;
		int newIndex = newRow * MAX_COLUMNS + col;
		if (newIndex < itemCount) selectedItemIndex_ = newIndex;
	}
	if (input.IsTrgDown(KEY_INPUT_LEFT))
	{
		sound.Play(SoundManager::SOUND::SE_SELECT);
		int newCol = col - 1;
		if (newCol >= 0)
		{
			int newIndex = row * MAX_COLUMNS + newCol;
			if (newIndex < itemCount) selectedItemIndex_ = newIndex;
		}
	}
	if (input.IsTrgDown(KEY_INPUT_RIGHT))
	{
		sound.Play(SoundManager::SOUND::SE_SELECT);
		int newCol = col + 1;
		int newIndex = row * MAX_COLUMNS + newCol;
		if (newIndex < itemCount) selectedItemIndex_ = newIndex;
	}

	if (input.IsTrgDown(KEY_INPUT_X))
	{
		sound.Play(SoundManager::SOUND::SE_CANCEL);
		Hide();
	}
}

void InventoryUI::Draw(void)
{
	if (!isVisible_) return;

	auto& itemManager = ItemManager::GetInstance();
	auto& font = Font::GetInstance();

	// 各種定数
	const int fontSize = 18;
	const int iconSize = ICON_SIZE;
	const int padding = PADDING;

	// アイテム取得
	int itemCount = 0;
	std::function<std::shared_ptr<ItemBase>(int)> getItemFunc;

	if (currentTab_ == TAB::Material)
	{
		itemCount = itemManager.GetMaterialItemCount();
		getItemFunc = [&](int i) -> std::shared_ptr<ItemBase> {
			return itemManager.GetMaterialItem(i);
			};
	}
	else
	{
		itemCount = itemManager.GetProductItemCount();
		getItemFunc = [&](int i) -> std::shared_ptr<ItemBase> {
			return itemManager.GetProductItem(i);
			};
	}

	// 表示行数と列数の決定
	const int maxColumns = MAX_COLUMNS;
	const int rowCount = (itemCount + maxColumns - 1) / maxColumns;

	// グリッド全体のサイズ
	const int gridWidth = maxColumns * (iconSize + padding) - padding;
	const int gridHeight = rowCount * (iconSize * 2 + padding); // アイコン+名前+数量のため2倍

	// 中央揃えの描画開始位置
	const int startX = (Application::SCREEN_SIZE_X - gridWidth) / 2;
	const int startY = (Application::SCREEN_SIZE_Y - gridHeight) / 2;

	// ここでグリッド描画領域の背景を黒く半透明に塗る
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawBox(startX - 10, 80, startX + gridWidth + 10, startY + gridHeight + 30, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawBox(startX - 10, 80, startX + gridWidth + 10, startY + gridHeight + 30, GetColor(255, 255, 255), FALSE);

	// タブ表示
	const std::string materialText = "素材アイテム";
	const std::string productText = "完成品アイテム";

	int tabY = 40;
	int tabX = (Application::SCREEN_SIZE_X - font.GetDefaultTextWidth(materialText)) / 2;

	if (currentTab_ == TAB::Material)
	{
		font.DrawDefaultText(tabX, tabY, materialText.c_str(), GetColor(255, 255, 0), 24);
	}
	else if (currentTab_ == TAB::Product)
	{
		tabX = (Application::SCREEN_SIZE_X - font.GetDefaultTextWidth(productText)) / 2;
		font.DrawDefaultText(tabX, tabY, productText.c_str(), GetColor(255, 255, 0), 24);
	}

	// アイテム描画ループ
	for (int i = 0; i < itemCount; ++i)
	{
		auto item = getItemFunc(i);
		if (!item) continue;

		int row = i / maxColumns;
		int col = i % maxColumns;

		int x = startX + col * (iconSize + padding);
		int y = startY + row * (iconSize * 2 + padding);

		DrawGraph(x, y, item->GetImageHandle(), true);
		font.DrawDefaultText(x, y + iconSize + 4, item->GetName().c_str(), GetColor(255, 255, 255), 12);

		std::string quantityStr = "x" + std::to_string(item->GetQuantity());
		font.DrawDefaultText(x, y + iconSize + 24, quantityStr.c_str(), GetColor(200, 200, 200), 12);

		if (i == selectedItemIndex_)
		{
			const int border = 3;
			int color = GetColor(255, 255, 0);
			DrawBox(x - border, y - border, x + iconSize + border, y + iconSize + border, color, false);
		}
	}

	// 説明文（選択中）
	if (selectedItemIndex_ >= 0 && selectedItemIndex_ < itemCount)
	{
		auto selectedItem = getItemFunc(selectedItemIndex_);
		if (selectedItem)
		{
			const std::string& description = selectedItem->GetDescription();
			int descWidth = font.GetDefaultTextWidth(description);
			int descX = (Application::SCREEN_SIZE_X - descWidth) / 2;
			int descY = startY + gridHeight + 80;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawBox(descX - 10, descY - 5, descX + descWidth + 10, descY + fontSize + 10, GetColor(60, 60, 60), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			font.DrawDefaultText(descX, descY, description.c_str(), GetColor(255, 255, 255), fontSize);
		}
	}
}
