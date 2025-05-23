#include "InventoryUI.h"

#include <DxLib.h>
#include <functional>

#include "../../Manager/Generic/InputManager.h"
#include "../../Object/Manager/ItemManager.h"
#include "../../DrawUI/Font.h"

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

void InventoryUI::Update(void)
{
	auto& input = InputManager::GetInstance();
	auto& itemManager = ItemManager::GetInstance();

	// インベントリ表示切替トグル（Zキー）
	if (input.IsTrgDown(KEY_INPUT_Z))
	{
		isVisible_ = !isVisible_;

		// 表示したら選択初期化
		if (isVisible_)
		{
			selectedItemIndex_ = 0;
			currentTab_ = TAB::Material;
		}
	}

	if (!isVisible_) return;

	frameCount_++;

	// タブ切り替え（Xキーで切り替え）
	if (input.IsTrgDown(KEY_INPUT_X))
	{
		// タブ切り替え
		if (currentTab_ == TAB::Material)
		{
			currentTab_ = TAB::Product;
		}
		else
		{
			currentTab_ = TAB::Material;
		}

		// 選択インデックスリセット
		selectedItemIndex_ = 0;
	}

	// 現在のアイテム数（タブによって変化）
	int itemCount = 0;
	if (currentTab_ == TAB::Material)
	{
		itemCount = itemManager.GetMaterialItemCount();
	}
	else // Productタブ
	{
		itemCount = itemManager.GetProductItemCount();
	}

	// 選択が範囲外なら修正
	if (selectedItemIndex_ >= itemCount) selectedItemIndex_ = itemCount - 1;
	if (selectedItemIndex_ < 0) selectedItemIndex_ = 0;

	// 選択行・列計算
	int row = selectedItemIndex_ / MAX_COLUMNS;
	int col = selectedItemIndex_ % MAX_COLUMNS;

	// 矢印キーで移動（上下左右）
	if (input.IsTrgDown(KEY_INPUT_UP))
	{
		int newRow = row - 1;
		if (newRow >= 0)
		{
			int newIndex = newRow * MAX_COLUMNS + col;
			if (newIndex < itemCount)
				selectedItemIndex_ = newIndex;
		}
	}

	if (input.IsTrgDown(KEY_INPUT_DOWN))
	{
		int newRow = row + 1;
		int newIndex = newRow * MAX_COLUMNS + col;
		if (newIndex < itemCount)
			selectedItemIndex_ = newIndex;
	}

	if (input.IsTrgDown(KEY_INPUT_LEFT))
	{
		int newCol = col - 1;
		if (newCol >= 0)
		{
			int newIndex = row * MAX_COLUMNS + newCol;
			if (newIndex < itemCount)
				selectedItemIndex_ = newIndex;
		}
	}

	if (input.IsTrgDown(KEY_INPUT_RIGHT))
	{
		int newCol = col + 1;
		int newIndex = row * MAX_COLUMNS + newCol;
		if (newIndex < itemCount)
			selectedItemIndex_ = newIndex;
	}
}

void InventoryUI::Draw(void)
{
	if (!isVisible_) return;

	auto& itemManager = ItemManager::GetInstance();

	// 描画開始座標
	const int startX = 50;
	const int startY = 50;

	// テキスト表示部分の高さ
	const int textAreaHeight = 64;

	// テキスト背景の余白
	const int boxPadding = 4;

	const int bgHeight = 400;

	// 現在のアイテム数（タブで変化）
	int itemCount = 0;

	// アイテムを取得する関数ポインタを用意（共通化用）
	std::function<std::shared_ptr<ItemBase>(int)> getItemFunc;

	// タブに応じて取得関数とアイテム数を切り替え
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

	// タブ名描画
	const int tabX = startX;
	const int tabY = startY - 40;
	int colorMaterial = GetColor(255, 255, 255);
	int colorProduct = GetColor(255, 255, 255);
	if (currentTab_ == TAB::Material) colorMaterial = GetColor(255, 255, 0);
	else colorProduct = GetColor(255, 255, 0);

	switch (currentTab_)
	{
	case InventoryUI::TAB::Material:
		Font::GetInstance().DrawDefaultText(tabX, tabY, "素材アイテム", colorMaterial, 24);
		break;
	case InventoryUI::TAB::Product:
		Font::GetInstance().DrawDefaultText(tabX, tabY, "完成品アイテム", colorProduct, 24);
		break;
	}

	// アイテム一覧描画
	for (int i = 0; i < itemCount; i++)
	{
		auto item = getItemFunc(i);
		if (!item) continue;

		// アイテムのグリッド位置計算
		int row = i / MAX_COLUMNS;
		int col = i % MAX_COLUMNS;

		int x = startX + col * (ICON_SIZE + PADDING);
		int y = startY + row * (ICON_SIZE + PADDING + ICON_SIZE);

		// アイテム画像を描画（透過有効）
		DrawGraph(x, y, item->GetImageHandle(), true);

		// アイテム名を描画
		Font::GetInstance().DrawDefaultText(x, y + ICON_SIZE + 4, item->GetName().c_str(), GetColor(255, 255, 255), 12);

		// 所持数を描画
		std::string quantityStr = "x" + std::to_string(item->GetQuantity());
		Font::GetInstance().DrawDefaultText(x, y + ICON_SIZE + 24, quantityStr.c_str(), GetColor(200, 200, 200), 12);

		// 選択中のアイテムには黄色い枠線を描画
		if (i == selectedItemIndex_)
		{
			const int borderThickness = 3;
			int color = GetColor(255, 255, 0);
			DrawBox(x - borderThickness, y - borderThickness, x + ICON_SIZE + borderThickness, y + ICON_SIZE + borderThickness, color, false);
		}
	}

	// 選択中アイテムの説明を表示
	if (selectedItemIndex_ >= 0 && selectedItemIndex_ < itemCount)
	{
		auto selectedItem = getItemFunc(selectedItemIndex_);
		if (selectedItem)
		{
			const int descX = startX;
			const int descY = startY + bgHeight + 20;

			const std::string& description = selectedItem->GetDescription();
			const int fontSize = 18;

			// 説明テキストの背景ボックスを描画（半透明）
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawBox(descX - 10, descY - 5, descX + 500, descY + 60, GetColor(60, 60, 60), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// 説明テキストを描画
			Font::GetInstance().DrawDefaultText(descX, descY, description.c_str(), GetColor(255, 255, 255), fontSize);
		}
	}
}
