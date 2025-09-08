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
    currentTab_ = TAB::Material;
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

    // --- 表示対象アイテムリストを作成 ---
    visibleItems_.clear();
    int itemCount = (currentTab_ == TAB::Material)
        ? itemManager.GetMaterialItemCount()
        : itemManager.GetProductItemCount();

    for (int i = 0; i < itemCount; ++i) {
        std::shared_ptr<ItemBase> item;
        if (currentTab_ == TAB::Material) {
            item = itemManager.GetMaterialItem(i);
        }
        else {
            item = itemManager.GetProductItem(i);
        }

        if (item && item->GetQuantity() > 0) {
            visibleItems_.push_back(item);
        }
    }

    // --- 入力処理 ---
    if (visibleItems_.empty()) return; // 表示アイテムがなければ終了

    selectedItemIndex_ = std::clamp(selectedItemIndex_, 0, (int)visibleItems_.size() - 1);

    int row = selectedItemIndex_ / MAX_COLUMNS;
    int col = selectedItemIndex_ % MAX_COLUMNS;

    if (input.IsTrgDown(KEY_INPUT_UP)) {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        if (row > 0) selectedItemIndex_ -= MAX_COLUMNS;
    }
    if (input.IsTrgDown(KEY_INPUT_DOWN)) {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        if (selectedItemIndex_ + MAX_COLUMNS < (int)visibleItems_.size())
            selectedItemIndex_ += MAX_COLUMNS;
    }
    if (input.IsTrgDown(KEY_INPUT_LEFT)) {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        if (col > 0) selectedItemIndex_ -= 1;
    }
    if (input.IsTrgDown(KEY_INPUT_RIGHT)) {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        if (col < MAX_COLUMNS - 1 && selectedItemIndex_ + 1 < (int)visibleItems_.size())
            selectedItemIndex_ += 1;
    }

    if (input.IsTrgDown(KEY_INPUT_ESCAPE)) {
        sound.Play(SoundManager::SOUND::SE_CANCEL);
        Hide();
    }
}

void InventoryUI::Draw(void)
{
    if (!isVisible_) return;

    auto& font = Font::GetInstance();

    // 各種定数
    const int fontSize = 24;
    const int iconSize = ICON_SIZE;
    const int padding = PADDING;

    // 表示行数と列数の決定
    const int maxColumns = MAX_COLUMNS;
    const int rowCount = (visibleItems_.size() + maxColumns - 1) / maxColumns;

    // グリッド全体のサイズ
    const int gridWidth = maxColumns * (iconSize + padding) - padding;
    const int gridHeight = rowCount * (iconSize * 2 + padding);

    // 中央揃えの描画開始位置
    const int startX = 150;
    const int startY = 150;

    // 背景
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    DrawBox(startX - 100, 140, startX + gridWidth + 200, startY + gridHeight + (Application::DEFA_SCREEN_SZIE_Y / 2) + 200, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawBox(startX - 100, 140, startX + gridWidth + 200, startY + gridHeight + (Application::DEFA_SCREEN_SZIE_Y / 2) + 200, GetColor(255, 255, 255), FALSE);

    // アイテム描画ループ
    for (int i = 0; i < (int)visibleItems_.size(); ++i)
    {
        auto item = visibleItems_[i];
        if (!item) continue;

        int row = i / MAX_COLUMNS;
        int col = i % MAX_COLUMNS;

        int x = startX + col * (iconSize + padding);
        int y = startY + row * (iconSize * 2 + padding);

        // アイコン
        DrawGraph(x, y, item->GetImageHandle(), true);

        // 名前
        font.DrawDefaultText(x, y + iconSize + 4,
            item->GetName().c_str(),
            GetColor(255, 255, 255), 24,
            Font::FONT_TYPE_ANTIALIASING_EDGE);

        // 数量
        std::string quantityStr = "x" + std::to_string(item->GetQuantity());
        font.DrawDefaultText(x, y + iconSize + 24,
            quantityStr.c_str(),
            GetColor(200, 200, 200), 20,
            Font::FONT_TYPE_ANTIALIASING_EDGE);

        // 選択枠
        if (i == selectedItemIndex_) {
            const int border = 3;
            int color = GetColor(255, 255, 0);
            DrawBox(x - border, y - border, x + iconSize + border, y + iconSize + border, color, false);
        }
    }

    // 説明文（選択中）
    if (selectedItemIndex_ >= 0 && selectedItemIndex_ < (int)visibleItems_.size())
    {
        auto selectedItem = visibleItems_[selectedItemIndex_];
        if (selectedItem)
        {
            const std::string& description = selectedItem->GetDescription();
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
