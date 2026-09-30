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
    currentTab_ = TAB::MATERIAL;
    frameCount_ = 0;
}

LibraryUI::~LibraryUI(void)
{
}

void LibraryUI::Init(void)
{
    isVisible_ = false;
    selectedItemIndex_ = -1;
    currentTab_ = TAB::MATERIAL;
    frameCount_ = 0;
}

void LibraryUI::Show(void)
{
    isVisible_ = true;
    selectedItemIndex_ = 0;
    currentTab_ = TAB::MATERIAL;
}

void LibraryUI::Hide(void)
{
    isVisible_ = false;
}


void LibraryUI::Update(void)
{
    auto& input = InputManager::GetInstance();
    auto& itemManager = ItemManager::GetInstance();
    auto& sound = SoundManager::GetInstance();

    if (!isVisible_)
    {
        return;
    }

    frameCount_++;

    if (input.IsTriggerDown(KEY_INPUT_TAB))
    {
        sound.Play(SoundManager::SOUND::SE_PUSH);
        currentTab_ = (currentTab_ == TAB::MATERIAL) ? TAB::PRODUCT : TAB::MATERIAL;
        selectedItemIndex_ = 0;
    }

    int itemCount = (currentTab_ == TAB::MATERIAL)
        ? itemManager.GetMaterialItemCount()
        : itemManager.GetProductItemCount();

    selectedItemIndex_ = std::clamp(selectedItemIndex_, 0, std::max(0, itemCount - 1));

    int currentRow = selectedItemIndex_ / MAX_COLUMNS;
    int currentColumn = selectedItemIndex_ % MAX_COLUMNS;

    if (input.IsTriggerDown(KEY_INPUT_UP))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        int newRow = currentRow - 1;
        if (newRow >= 0)
        {
            int newIndex = newRow * MAX_COLUMNS + currentColumn;
            if (newIndex < itemCount)
            {
                selectedItemIndex_ = newIndex;
            }
        }
    }

    if (input.IsTriggerDown(KEY_INPUT_DOWN))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        int newRow = currentRow + 1;
        int newIndex = newRow * MAX_COLUMNS + currentColumn;
        if (newIndex < itemCount)
        {
            selectedItemIndex_ = newIndex;
        }
    }

    if (input.IsTriggerDown(KEY_INPUT_LEFT))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        int newColumn = currentColumn - 1;
        if (newColumn >= 0)
        {
            int newIndex = currentRow * MAX_COLUMNS + newColumn;
            if (newIndex < itemCount)
            {
                selectedItemIndex_ = newIndex;
            }
        }
    }

    if (input.IsTriggerDown(KEY_INPUT_RIGHT))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        int newColumn = currentColumn + 1;
        int newIndex = currentRow * MAX_COLUMNS + newColumn;
        if (newIndex < itemCount)
        {
            selectedItemIndex_ = newIndex;
        }
    }

    if (input.IsTriggerDown(KEY_INPUT_ESCAPE))
    {
        sound.Play(SoundManager::SOUND::SE_CANCEL);
        Hide();
    }
}

void LibraryUI::Draw(void)
{
    if (!isVisible_)
    {
        return;
    }

    auto& itemManager = ItemManager::GetInstance();
    auto& font = Font::GetInstance();

    // テキスト・描画関連のローカル定数
    const int FONT_SIZE_NAME = 24;
    const int FONT_SIZE_TAB = 28;
    const int TEXT_OFFSET_Y_NAME = 4;
    const int SELECTION_BORDER_WIDTH = 3;
    const int DESCRIPTION_ALPHA = 180;
    const int DESCRIPTION_OFFSET_X = 120;
    const int DESCRIPTION_OFFSET_Y_TOP = 5;
    const int DESCRIPTION_OFFSET_RIGHT = 50;
    const int DESCRIPTION_OFFSET_BOTTOM = 100;
    const int START_POSITION_X = 150;
    const int START_POSITION_Y = 150;
    const int TAB_POSITION_Y = 100;

    int itemCount = 0;
    std::function<std::shared_ptr<ItemBase>(int)> getItemFunction;

    if (currentTab_ == TAB::MATERIAL)
    {
        itemCount = itemManager.GetMaterialItemCount();
        getItemFunction = [&](int index) -> std::shared_ptr<ItemBase>
            {
            return itemManager.GetMaterialItem(index);
            };
    }
    else
    {
        itemCount = itemManager.GetProductItemCount();
        getItemFunction = [&](int index) -> std::shared_ptr<ItemBase> 
            {
            return itemManager.GetProductItem(index);
            };
    }

    int rowCount = (itemCount + MAX_COLUMNS - 1) / MAX_COLUMNS;
    int gridWidth = MAX_COLUMNS * (ICON_SIZE + PADDING) - PADDING;
    int gridHeight = rowCount * (ICON_SIZE * 2 + PADDING);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX);

    DrawBox(START_POSITION_X - BACKGROUND_OFFSET_X, BACKGROUND_OFFSET_Y_TOP, 
        START_POSITION_X + gridWidth + BACKGROUND_OFFSET_W, START_POSITION_Y 
        + gridHeight + (Application::FULL_SCREEN_SIZE_Y / 2) 
        + BACKGROUND_OFFSET_H, COLOR_BLACK, true);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawBox(START_POSITION_X - BACKGROUND_OFFSET_X, BACKGROUND_OFFSET_Y_TOP,
        START_POSITION_X + gridWidth + BACKGROUND_OFFSET_W, START_POSITION_Y 
        + gridHeight + (Application::FULL_SCREEN_SIZE_Y / 2) 
        + BACKGROUND_OFFSET_H, COLOR_WHITE, false);

    const std::string materialText = "素材アイテム";
    const std::string productText = "完成品アイテム";

    int tabPositionX = (Application::SCREEN_SIZE_X / 2) - font.GetDefaultTextWidth(materialText);

    if (currentTab_ == TAB::MATERIAL)
    {
        font.DrawDefaultText(tabPositionX, TAB_POSITION_Y, materialText.c_str(), 
            COLOR_YELLOW, FONT_SIZE_TAB, Font::FONT_TYPE_ANTIALIASING_EDGE);
    }
    else if (currentTab_ == TAB::PRODUCT)
    {
        tabPositionX = (Application::SCREEN_SIZE_X - font.GetDefaultTextWidth(productText)) / 2;
        font.DrawDefaultText(tabPositionX, TAB_POSITION_Y, productText.c_str(),
            COLOR_YELLOW, FONT_SIZE_TAB, Font::FONT_TYPE_ANTIALIASING_EDGE);
    }

    for (int index = 0; index < itemCount; ++index)
    {
        auto item = getItemFunction(index);
        if (!item)
        {
            continue;
        }

        int itemRow = index / MAX_COLUMNS;
        int itemColumn = index % MAX_COLUMNS;

        int drawPositionX = START_POSITION_X + itemColumn * (ICON_SIZE + PADDING);
        int drawPositionY = START_POSITION_Y + itemRow * (ICON_SIZE * 2 + PADDING);

        DrawBox(drawPositionX, drawPositionY, drawPositionX + ICON_SIZE,
            drawPositionY + ICON_SIZE, COLOR_GRAY, false);

        if (item->GetQuantity() > 0)
        {
            DrawGraph(drawPositionX, drawPositionY, item->GetImageHandle(), true);
            font.DrawDefaultText(
                drawPositionX, drawPositionY + ICON_SIZE + TEXT_OFFSET_Y_NAME,
                item->GetName().c_str(),
                COLOR_WHITE, FONT_SIZE_NAME,
                Font::FONT_TYPE_ANTIALIASING_EDGE
            );
        }
        else
        {
            font.DrawDefaultText(
                drawPositionX, drawPositionY + ICON_SIZE + TEXT_OFFSET_Y_NAME,
                "???",
                COLOR_DARK_GRAY, FONT_SIZE_NAME,
                Font::FONT_TYPE_ANTIALIASING_EDGE
            );
        }

        if (index == selectedItemIndex_)
        {
            DrawBox(drawPositionX - SELECTION_BORDER_WIDTH,
                drawPositionY - SELECTION_BORDER_WIDTH, drawPositionX 
                + ICON_SIZE + SELECTION_BORDER_WIDTH, drawPositionY
                + ICON_SIZE + SELECTION_BORDER_WIDTH, COLOR_YELLOW, false);
        }
    }

    if (selectedItemIndex_ >= 0 && selectedItemIndex_ < itemCount)
    {
        auto selectedItem = getItemFunction(selectedItemIndex_);
        if (selectedItem && selectedItem->GetQuantity() > 0)
        {
            const std::string& description = selectedItem->GetDescription();
            int descriptionPositionX = (Application::SCREEN_SIZE_X / 2) + DESCRIPTION_OFFSET_X;
            int descriptionPositionY = Application::FULL_SCREEN_SIZE_Y / 2;

            SetDrawBlendMode(DX_BLENDMODE_ALPHA, DESCRIPTION_ALPHA);

            DrawBox(descriptionPositionX, descriptionPositionY - DESCRIPTION_OFFSET_Y_TOP, 
                Application::FULL_SCREEN_SIZE_X - DESCRIPTION_OFFSET_RIGHT, descriptionPositionY 
                + FONT_SIZE_NAME + (Application::FULL_SCREEN_SIZE_Y / 2) 
                - DESCRIPTION_OFFSET_BOTTOM, COLOR_BLACK, true);

            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

            DrawBox(descriptionPositionX, descriptionPositionY - DESCRIPTION_OFFSET_Y_TOP,
                Application::FULL_SCREEN_SIZE_X - DESCRIPTION_OFFSET_RIGHT, descriptionPositionY
                + FONT_SIZE_NAME + (Application::FULL_SCREEN_SIZE_Y / 2)
                - DESCRIPTION_OFFSET_BOTTOM, COLOR_WHITE, false);

            font.DrawDefaultText(descriptionPositionX, descriptionPositionY, 
                description.c_str(), COLOR_WHITE, FONT_SIZE_NAME);
        }
    }
}