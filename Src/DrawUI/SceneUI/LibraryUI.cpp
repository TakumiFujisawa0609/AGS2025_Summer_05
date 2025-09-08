#define NOMINMAX
#include "LibraryUI.h"

#include <DxLib.h>
#include <functional>
#include <algorithm>

#include "../../Manager/Generic/InputManager.h"
#include "../../Object/Manager/ItemManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"


LibraryUI::LibraryUI(void)
{
	isVisible_ = false;
	selectedItemIndex_ = -1;
	currentTab_ = TAB::Material;
	frameCount_ = 0;
}

LibraryUI::~LibraryUI(void)
{
}

void LibraryUI::Init(void)
{
	isVisible_ = false;
	selectedItemIndex_ = -1;
	currentTab_ = TAB::Material; // 初期タブは素材
	frameCount_ = 0;
}

void  LibraryUI::Show(void)
{
	isVisible_ = true;
	selectedItemIndex_ = 0;
	currentTab_ = TAB::Material;
}

void  LibraryUI::Hide(void)
{
	isVisible_ = false;
}


void  LibraryUI::Update(void)
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

	if (input.IsTrgDown(KEY_INPUT_ESCAPE))
	{
		sound.Play(SoundManager::SOUND::SE_CANCEL);
		Hide();
	}
}

void  LibraryUI::Draw(void)
{
	if (!isVisible_) return;

	auto& itemManager = ItemManager::GetInstance();
	auto& font = Font::GetInstance();

	// 各種定数
	const int fontSize = 24;
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
	const int startX = 150;
	const int startY = 150;

	// ここでグリッド描画領域の背景を黒く半透明に塗る
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawBox(startX - 100, 140, startX + gridWidth + 200, startY + gridHeight + (Application::DEFA_SCREEN_SZIE_Y / 2) + 200, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawBox(startX - 100, 140, startX + gridWidth + 200, startY + gridHeight + (Application::DEFA_SCREEN_SZIE_Y / 2) + 200, GetColor(255, 255, 255), FALSE);

	// タブ表示
	const std::string materialText = "素材アイテム";
	const std::string productText = "完成品アイテム";

	int tabY = 100;
	int tabX = (Application::SCREEN_SIZE_X / 2) - font.GetDefaultTextWidth(materialText);

	if (currentTab_ == TAB::Material)
	{
		font.DrawDefaultText(tabX, tabY, materialText.c_str(), GetColor(255, 255, 0), 28, Font::FONT_TYPE_ANTIALIASING_EDGE);
	}
	else if (currentTab_ == TAB::Product)
	{
		tabX = (Application::SCREEN_SIZE_X - font.GetDefaultTextWidth(productText)) / 2;
		font.DrawDefaultText(tabX, tabY, productText.c_str(), GetColor(255, 255, 0), 28, Font::FONT_TYPE_ANTIALIASING_EDGE);
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

		// --- アイコン枠（全アイテム分表示）---
		int frameColor = GetColor(200, 200, 200);
		DrawBox(x, y, x + iconSize, y + iconSize, frameColor, false);

		// --- アイコンと名前 ---
		if (item->GetQuantity() > 0) {
			// 入手済み → アイコンあり & 名前表示
			DrawGraph(x, y, item->GetImageHandle(), true);
			font.DrawDefaultText(
				x, y + iconSize + 4,
				item->GetName().c_str(),
				GetColor(255, 255, 255), 24,
				Font::FONT_TYPE_ANTIALIASING_EDGE
			);
		}
		else {
			// 未入手 → アイコンなし & ??? 表示
			font.DrawDefaultText(
				x, y + iconSize + 4,
				"???",
				GetColor(150, 150, 150), 24,
				Font::FONT_TYPE_ANTIALIASING_EDGE
			);
		}

		// --- 選択中の枠ハイライト ---
		if (i == selectedItemIndex_) {
			const int border = 3;
			int color = GetColor(255, 255, 0);
			DrawBox(x - border, y - border, x + iconSize + border, y + iconSize + border, color, false);
		}
	}

	// 説明文（選択中）
	if (selectedItemIndex_ >= 0 && selectedItemIndex_ < itemCount)
	{
		auto selectedItem = getItemFunc(selectedItemIndex_);
		if (selectedItem && selectedItem->GetQuantity() > 0) // ← 入手済みのみ
		{
			const std::string& description = selectedItem->GetDescription();
			int descWidth = font.GetDefaultTextWidth(description);
			int descX = (Application::SCREEN_SIZE_X / 2) + 120;
			int descY = Application::DEFA_SCREEN_SZIE_Y / 2;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawBox(descX, descY - 5, Application::DEFA_SCREEN_SIZE_X - 50, descY + fontSize + (Application::DEFA_SCREEN_SZIE_Y / 2) - 100, GetColor(0, 0, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			DrawBox(descX, descY - 5, Application::DEFA_SCREEN_SIZE_X - 50, descY + fontSize + (Application::DEFA_SCREEN_SZIE_Y / 2) - 100, GetColor(255, 255, 255), false);

			font.DrawDefaultText(descX, descY, description.c_str(), GetColor(255, 255, 255), fontSize);
		}
	}

}
