#include "InventoryUI.h"

#include <DxLib.h>
#include <functional>

#include "../../Manager/Generic/InputManager.h"
#include "../../Object/Manager/ItemManager.h"
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

	// 各種定数
	const int textAreaHeight = 64;
	const int boxPadding = 4;
	const int fontSize = 18;

	// アイテム数と取得関数
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

	// 描画開始位置を中央に調整
	const int numRows = (itemCount + MAX_COLUMNS - 1) / MAX_COLUMNS;
	const int gridWidth = MAX_COLUMNS * (ICON_SIZE + PADDING) - PADDING;
	const int gridHeight = numRows * (ICON_SIZE * 2 + PADDING); // アイコン+名前+数

	const int startX = (Application::SCREEN_SIZE_X - gridWidth) / 2;
	const int startY = 100;

	// タブ表示（上部中央）
	const std::string materialText = "素材アイテム";
	const std::string productText = "完成品アイテム";

	int materialColor = GetColor(255, 255, 255);
	int productColor = GetColor(255, 255, 255);
	if (currentTab_ == TAB::Material) materialColor = GetColor(255, 255, 0);
	else productColor = GetColor(255, 255, 0);

	int materialWidth = Font::GetInstance().GetDefaultTextWidth(materialText);
	int productWidth = Font::GetInstance().GetDefaultTextWidth(productText);

	int tabY = 40;
	int tabSpacing = 40;
	int totalTabWidth = materialWidth + productWidth + tabSpacing;

	int tabX = (Application::SCREEN_SIZE_X - totalTabWidth) / 2;
	switch (currentTab_)
	{
	case TAB::Material:
		Font::GetInstance().DrawDefaultText(tabX, tabY, materialText.c_str(), materialColor, 24);
		break;

	case TAB::Product:
		Font::GetInstance().DrawDefaultText(tabX, tabY, productText.c_str(), productColor, 24);
		break;

	default:
		break;
	}

	// アイテム一覧
	for (int i = 0; i < itemCount; ++i)
	{
		auto item = getItemFunc(i);
		if (!item) continue;

		int row = i / MAX_COLUMNS;
		int col = i % MAX_COLUMNS;

		int x = startX + col * (ICON_SIZE + PADDING);
		int y = startY + row * (ICON_SIZE + PADDING + ICON_SIZE);

		// 画像
		DrawGraph(x, y, item->GetImageHandle(), true);

		// 名前
		Font::GetInstance().DrawDefaultText(x, y + ICON_SIZE + 4, item->GetName().c_str(), GetColor(255, 255, 255), 12);

		// 数量
		std::string quantityStr = "x" + std::to_string(item->GetQuantity());
		Font::GetInstance().DrawDefaultText(x, y + ICON_SIZE + 24, quantityStr.c_str(), GetColor(200, 200, 200), 12);

		// 選択枠
		if (i == selectedItemIndex_)
		{
			const int border = 3;
			int color = GetColor(255, 255, 0);
			DrawBox(x - border, y - border, x + ICON_SIZE + border, y + ICON_SIZE + border, color, false);
		}
	}

	// 選択中アイテムの説明描画（画面下部中央）
	if (selectedItemIndex_ >= 0 && selectedItemIndex_ < itemCount)
	{
		auto selectedItem = getItemFunc(selectedItemIndex_);
		if (selectedItem)
		{
			const std::string& description = selectedItem->GetDescription();

			int descWidth = Font::GetInstance().GetDefaultTextWidth(description);
			int descX = (Application::SCREEN_SIZE_X - descWidth) / 2;
			int descY = startY + gridHeight + 40;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawBox(descX - 10, descY - 5, descX + descWidth + 10, descY + fontSize + 10, GetColor(60, 60, 60), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			Font::GetInstance().DrawDefaultText(descX, descY, description.c_str(), GetColor(255, 255, 255), fontSize);
		}
	}
}
