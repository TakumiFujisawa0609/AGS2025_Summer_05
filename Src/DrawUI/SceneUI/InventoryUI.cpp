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
    , currentTab_(TAB::MATERIAL)
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
    currentTab_ = TAB::MATERIAL;
    frameCount_ = 0;
}

void InventoryUI::Show(void)
{
    isVisible_ = true;
    selectedItemIndex_ = 0;
    currentTab_ = TAB::MATERIAL;
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

    if (!isVisible_)
    {
        return;
    }

    frameCount_++;

    visibleItems_.clear();
    int itemCount = (currentTab_ == TAB::MATERIAL)
        ? itemManager.GetMaterialItemCount()
        : itemManager.GetProductItemCount();

    for (int index = 0; index < itemCount; ++index)
    {
        std::shared_ptr<ItemBase> item;
        if (currentTab_ == TAB::MATERIAL)
        {
            item = itemManager.GetMaterialItem(index);
        }
        else
        {
            item = itemManager.GetProductItem(index);
        }

        if (item && item->GetQuantity() > 0)
        {
            visibleItems_.push_back(item);
        }
    }

    if (visibleItems_.empty())
    {
        return;
    }

    selectedItemIndex_ = std::clamp(selectedItemIndex_, 0,
        static_cast<int>(visibleItems_.size()) - 1);

    int currentRow = selectedItemIndex_ / MAX_COLUMNS;
    int currentColumn = selectedItemIndex_ % MAX_COLUMNS;

    if (input.IsTriggerDown(KEY_INPUT_UP))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        if (currentRow > 0)
        {
            selectedItemIndex_ -= MAX_COLUMNS;
        }
    }

    if (input.IsTriggerDown(KEY_INPUT_DOWN))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        if (selectedItemIndex_ + MAX_COLUMNS < static_cast<int>(visibleItems_.size()))
        {
            selectedItemIndex_ += MAX_COLUMNS;
        }
    }

    if (input.IsTriggerDown(KEY_INPUT_LEFT))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        if (currentColumn > 0)
        {
            selectedItemIndex_ -= 1;
        }
    }

    if (input.IsTriggerDown(KEY_INPUT_RIGHT))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        if (currentColumn < MAX_COLUMNS - 1 && selectedItemIndex_ + 1 
            < static_cast<int>(visibleItems_.size()))
        {
            selectedItemIndex_ += 1;
        }
    }

    if (input.IsTriggerDown(KEY_INPUT_ESCAPE))
    {
        sound.Play(SoundManager::SOUND::SE_CANCEL);
        Hide();
    }
}

void InventoryUI::Draw(void)
{
    if (!isVisible_)
    {
        return;
    }

    auto& font = Font::GetInstance();

    // テキスト・描画関連のローカル定数
    const int FONT_SIZE_NAME = 24;
    const int FONT_SIZE_QUANTITY = 20;
    const int FONT_SIZE_DESCRIPTION = 24;
    const unsigned int COLOR_GRAY = 0xc8c8c8;
    const int TEXT_OFFSET_Y_NAME = 4;
    const int TEXT_OFFSET_Y_QUANTITY = 24;
    const int SELECTION_BORDER_WIDTH = 3;
    const int DESCRIPTION_ALPHA = 180;
    const int DESCRIPTION_OFFSET_X = 120;
    const int DESCRIPTION_OFFSET_Y_TOP = 5;
    const int DESCRIPTION_OFFSET_RIGHT = 50;
    const int DESCRIPTION_OFFSET_BOTTOM = 100;
    const int START_POSITION_X = 150;
    const int START_POSITION_Y = 150;

    int rowCount = (static_cast<int>(visibleItems_.size()) + MAX_COLUMNS - 1) / MAX_COLUMNS;
    int gridWidth = MAX_COLUMNS * (ICON_SIZE + PADDING) - PADDING;
    int gridHeight = rowCount * (ICON_SIZE * 2 + PADDING);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX);

    DrawBox(START_POSITION_X - BACKGROUND_OFFSET_X, BACKGROUND_OFFSET_Y_TOP, START_POSITION_X
        + gridWidth + BACKGROUND_OFFSET_W, START_POSITION_Y + gridHeight + 
        (Application::FULL_SCREEN_SIZE_Y / 2) + BACKGROUND_OFFSET_H, COLOR_BLACK, true);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawBox(START_POSITION_X - BACKGROUND_OFFSET_X, BACKGROUND_OFFSET_Y_TOP, START_POSITION_X
        + gridWidth + BACKGROUND_OFFSET_W, START_POSITION_Y + gridHeight + 
        (Application::FULL_SCREEN_SIZE_Y / 2) + BACKGROUND_OFFSET_H, COLOR_WHITE, false);

    for (int index = 0; index < static_cast<int>(visibleItems_.size()); ++index)
    {
        auto item = visibleItems_[index];
        if (!item)
        {
            continue;
        }

        int itemRow = index / MAX_COLUMNS;
        int itemColumn = index % MAX_COLUMNS;

        int drawPositionX = START_POSITION_X + itemColumn * (ICON_SIZE + PADDING);
        int drawPositionY = START_POSITION_Y + itemRow * (ICON_SIZE * 2 + PADDING);

        DrawGraph(drawPositionX, drawPositionY, item->GetImageHandle(), true);

        font.DrawDefaultText(drawPositionX, drawPositionY + ICON_SIZE + TEXT_OFFSET_Y_NAME,
            item->GetName().c_str(),
            COLOR_WHITE, FONT_SIZE_NAME,
            Font::FONT_TYPE_ANTIALIASING_EDGE);

        std::string quantityString = "x" + std::to_string(item->GetQuantity());
        font.DrawDefaultText(drawPositionX, drawPositionY + ICON_SIZE + TEXT_OFFSET_Y_QUANTITY,
            quantityString.c_str(),
            COLOR_GRAY, FONT_SIZE_QUANTITY,
            Font::FONT_TYPE_ANTIALIASING_EDGE);

        if (index == selectedItemIndex_)
        {
            DrawBox(drawPositionX - SELECTION_BORDER_WIDTH, drawPositionY - 
                SELECTION_BORDER_WIDTH, drawPositionX + ICON_SIZE + SELECTION_BORDER_WIDTH,
                drawPositionY + ICON_SIZE + SELECTION_BORDER_WIDTH, COLOR_YELLOW, false);
        }
    }

    if (selectedItemIndex_ >= 0 && selectedItemIndex_ < static_cast<int>(visibleItems_.size()))
    {
        auto selectedItem = visibleItems_[selectedItemIndex_];
        if (selectedItem)
        {
            const std::string& description = selectedItem->GetDescription();
            int descriptionPositionX = (Application::SCREEN_SIZE_X / 2) + DESCRIPTION_OFFSET_X;
            int descriptionPositionY = Application::FULL_SCREEN_SIZE_Y / 2;

            SetDrawBlendMode(DX_BLENDMODE_ALPHA, DESCRIPTION_ALPHA);

            DrawBox(descriptionPositionX, descriptionPositionY - DESCRIPTION_OFFSET_Y_TOP, 
                Application::FULL_SCREEN_SIZE_X - DESCRIPTION_OFFSET_RIGHT, descriptionPositionY 
                + FONT_SIZE_DESCRIPTION + (Application::FULL_SCREEN_SIZE_Y / 2)
                - DESCRIPTION_OFFSET_BOTTOM, COLOR_BLACK, true);

            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

            DrawBox(descriptionPositionX, descriptionPositionY - DESCRIPTION_OFFSET_Y_TOP,
                Application::FULL_SCREEN_SIZE_X - DESCRIPTION_OFFSET_RIGHT, descriptionPositionY 
                + FONT_SIZE_DESCRIPTION + (Application::FULL_SCREEN_SIZE_Y / 2)
                - DESCRIPTION_OFFSET_BOTTOM, COLOR_WHITE, false);

            font.DrawDefaultText(descriptionPositionX, descriptionPositionY,
                description.c_str(), COLOR_WHITE, FONT_SIZE_DESCRIPTION);
        }
    }
}