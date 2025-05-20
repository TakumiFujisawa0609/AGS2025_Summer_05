#include "InventoryUI.h"

#include<DxLib.h>

#include"../../Manager/Generic/InputManager.h"
#include"../../Object/Manager/ItemManager.h"
#include"../../DrawUI/Font.h"

InventoryUI::InventoryUI(ItemManager& manager) : itemManager_(manager)
{
	isVisible_ = false;
	selectedItemIndex_ = -1;
	frameCount_ = 0;
}

void InventoryUI::Update(void)
{
	//表示トグル
	if (InputManager::GetInstance().IsNew(KEY_INPUT_Z))
	{
		isVisible_ = !isVisible_;
	}

	if (!isVisible_) return;

	frameCount_++;

	//選択移動
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_UP))
	{
		selectedItemIndex_++;
		if (selectedItemIndex_ >= itemManager_.GetItemCount())
		{
			selectedItemIndex_ = 0;
		}
	}
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_DOWN))
	{
		selectedItemIndex_--;
		if (selectedItemIndex_ < 0)
		{
			selectedItemIndex_ = itemManager_.GetItemCount() - 1;
		}
	}
}

void InventoryUI::Draw(void)
{
	if (!isVisible_) return;

	//アイテムアイコンサイズ
	const int iconSize = 64;

	//各アイテムの間隔
	const int padding = 5;

	//横に並べる最大数
	const int maxColumns = 5;

	//開始X座標
	const int startX = 50;

	//開始Y座標
	const int startY = 50;

	// テキスト表示部分の高さ
	const int textAreaHeight = 64;

	// テキスト背景の余白
	const int boxPadding = 4;                 

	for (int i = 0; i < itemManager_.GetItemCount(); i++)
	{
		auto item = itemManager_.GetItem(i);
		if (!item) continue;

		// グリッド位置計算
		int row = i / maxColumns;
		int col = i % maxColumns;

		int x = startX + col * (iconSize + padding + 50);
		int y = startY + row * (iconSize + padding + 60);

		// 選択中なら点滅
		bool isSelected = (i == selectedItemIndex_);
		if (isSelected && (frameCount_ / 30) % 2 == 0)
		{
			continue; // 点滅
		}

		// アイテム画像
		DrawGraph(x, y, item->GetImageHandle(), true);

		// テキスト背景ボックス
		int boxX1 = x - boxPadding;
		int boxY1 = y + iconSize + 2;
		int boxX2 = x + iconSize + boxPadding;
		int boxY2 = boxY1 + textAreaHeight;
		DrawBox(boxX1, boxY1, boxX2, boxY2, GetColor(100, 100, 100), false);

		// アイテム名
		Font::GetInstance().DrawDefaultText(x, y + iconSize + 4,item->GetName().c_str(), GetColor(255, 255, 255), 18);

		// 所持数
		std::string quantityStr = "x" + std::to_string(item->GetQuantity());
		Font::GetInstance().DrawDefaultText(x, y + iconSize + 24,quantityStr.c_str(), GetColor(200, 200, 200), 16);
	}
}
