#include "Shop.h"

#include <DxLib.h>
#include <algorithm>
#include <random>

#include "../../Manager/Generic/InputManager.h"
#include "../../DrawUI/Font.h"
#include "../../Object/Manager/ItemManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Manager/System/DateTimeManager.h"
#include "../../Object/player.h"
#include "../../Application.h"
#include "../PlayerStop.h"

Shop::Shop(void)
    : selectedItemIndex_(0),
    isVisible_(false),
    skipFirstInputFrame_(true),
    currentPhase_(SHOP_PHASE::SELECT_ITEM),
    selectedQuantity_(1),
    currentArea_(SHOP_AREA::ITEM_LIST),
    purchaseListSelectedIndex_(0),
    lastDay_(-1),
    dateTimeManager_(nullptr)
{
}

Shop::~Shop(void)
{
}

void Shop::SetPlayer(std::shared_ptr<Player> player)
{
    player_ = player;
}

void Shop::SetDateTimeManager(DateTimeManager* dateTime)
{
    dateTimeManager_ = dateTime;
}

int Shop::GetPrice(std::shared_ptr<ItemBase> item) const
{
    if (item != nullptr)
    {
        return item->GetPrice();
    }
    return 0;
}

int Shop::GetTotalPrice(void) const
{
    int total = 0;

    for (const auto& entry : purchaseQuantities_)
    {
        auto item = ItemManager::GetInstance().FindItemById(entry.first);

        if (item != nullptr)
        {
            total += item->GetPrice() * entry.second;
        }
    }

    return total;
}

int Shop::GetSelectedQuantity(void) const
{
    auto item = GetSelectedItem();

    if (item == nullptr)
    {
        return 0;
    }

    auto iterator = purchaseQuantities_.find(item->GetId());

    if (iterator != purchaseQuantities_.end())
    {
        return iterator->second;
    }

    return 0;
}

void Shop::Init(void)
{
    purchaseQuantities_.clear();
    selectedItemIndex_ = 0;
    currentArea_ = SHOP_AREA::ITEM_LIST;
    purchaseListSelectedIndex_ = 0;

    RefreshDailyItems();
}

void Shop::Show(void)
{
    isVisible_ = true;
    Init();
}

void Shop::Hide(void)
{
    isVisible_ = false;
}

bool Shop::IsVisible(void) const
{
    return isVisible_;
}

void Shop::Update(void)
{
    if (!isVisible_)
    {
        return;
    }

    auto& inputManager = InputManager::GetInstance();
    auto& soundManager = SoundManager::GetInstance();

    if (dateTimeManager_ != nullptr)
    {
        int currentDay = dateTimeManager_->GetDay();

        if (lastDay_ != currentDay)
        {
            lastDay_ = currentDay;
            RefreshDailyItems();
        }
    }

    if (skipFirstInputFrame_)
    {
        skipFirstInputFrame_ = false;
        return;
    }

    switch (currentPhase_)
    {
    case SHOP_PHASE::SELECT_ITEM:
    {
        if (currentArea_ == SHOP_AREA::ITEM_LIST)
        {
            int totalItems = static_cast<int>(shopItems_.size());
            int column = selectedItemIndex_ % SHOP_COLUMNS;

            if (inputManager.IsTriggerDown(KEY_INPUT_LEFT))
            {
                soundManager.Play(SoundManager::SOUND::SE_SELECT);

                if (column > 0)
                {
                    selectedItemIndex_--;
                }
            }
            else if (inputManager.IsTriggerDown(KEY_INPUT_RIGHT))
            {
                soundManager.Play(SoundManager::SOUND::SE_SELECT);

                if (column < SHOP_COLUMNS - 1 && selectedItemIndex_ + 1 < totalItems)
                {
                    selectedItemIndex_++;
                }
            }

            if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
            {
                soundManager.Play(SoundManager::SOUND::SE_PUSH);
                currentPhase_ = SHOP_PHASE::SELECT_AMOUNT;
                selectedQuantity_ = GetSelectedQuantity();

                if (selectedQuantity_ <= 0)
                {
                    selectedQuantity_ = 1;
                }
            }

            if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
            {
                soundManager.Play(SoundManager::SOUND::SE_CANCEL);
                Hide();
                PlayerStop::GetInstance().ResumeMovement();
            }

            if (inputManager.IsTriggerDown(KEY_INPUT_TAB))
            {
                soundManager.Play(SoundManager::SOUND::SE_PUSH);
                currentArea_ = SHOP_AREA::PURCHASE_LIST;
                purchaseListSelectedIndex_ = 0;
            }
        }
        else
        {
            int itemCount = 0;

            for (const auto& entry : purchaseQuantities_)
            {
                if (entry.second > 0)
                {
                    itemCount++;
                }
            }

            int listSize = itemCount + 1;

            if (inputManager.IsTriggerDown(KEY_INPUT_UP))
            {
                soundManager.Play(SoundManager::SOUND::SE_SELECT);
                purchaseListSelectedIndex_ = (purchaseListSelectedIndex_ - 1 + listSize) % listSize;
            }
            else if (inputManager.IsTriggerDown(KEY_INPUT_DOWN))
            {
                soundManager.Play(SoundManager::SOUND::SE_SELECT);
                purchaseListSelectedIndex_ = (purchaseListSelectedIndex_ + 1) % listSize;
            }

            if (purchaseListSelectedIndex_ < itemCount)
            {
                auto iterator = std::next(purchaseQuantities_.begin(), purchaseListSelectedIndex_);

                if (inputManager.IsTriggerDown(KEY_INPUT_LEFT) && iterator->second > 1)
                {
                    soundManager.Play(SoundManager::SOUND::SE_SELECT);
                    iterator->second--;
                }
                else if (inputManager.IsTriggerDown(KEY_INPUT_RIGHT))
                {
                    soundManager.Play(SoundManager::SOUND::SE_SELECT);
                    iterator->second++;
                }
            }
            else
            {
                if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
                {
                    soundManager.Play(SoundManager::SOUND::SE_PUSH);
                    ConfirmPurchase();
                    purchaseListSelectedIndex_ = 0;
                }
            }

            if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
            {
                soundManager.Play(SoundManager::SOUND::SE_CANCEL);
                Hide();
            }

            if (inputManager.IsTriggerDown(KEY_INPUT_TAB))
            {
                soundManager.Play(SoundManager::SOUND::SE_PUSH);
                currentArea_ = SHOP_AREA::ITEM_LIST;
            }
        }
        break;
    }
    case SHOP_PHASE::SELECT_AMOUNT:
    {
        if (inputManager.IsTriggerDown(KEY_INPUT_UP))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            selectedQuantity_++;
        }
        else if (inputManager.IsTriggerDown(KEY_INPUT_DOWN))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);

            if (selectedQuantity_ > 1)
            {
                selectedQuantity_--;
            }
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
        {
            soundManager.Play(SoundManager::SOUND::SE_PUSH);
            auto item = GetSelectedItem();

            if (item != nullptr)
            {
                purchaseQuantities_[item->GetId()] = selectedQuantity_;
            }

            currentPhase_ = SHOP_PHASE::SELECT_ITEM;
            currentArea_ = SHOP_AREA::PURCHASE_LIST;
            purchaseListSelectedIndex_ = 0;
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            soundManager.Play(SoundManager::SOUND::SE_CANCEL);
            currentPhase_ = SHOP_PHASE::SELECT_ITEM;
        }
        break;
    }
    }
}

void Shop::Draw(void)
{
    if (!isVisible_)
    {
        return;
    }

    PlayerStop::GetInstance().StopMovement();

    const int screenWidth = Application::SCREEN_SIZE_X;
    const int screenHeight = Application::SCREEN_SIZE_Y;

    const int BOX_WIDTH_OFFSET = 100;                   // ボックス幅のオフセット
    const int START_Y = 100;                            // 描画開始Y座標
    const int FONT_SIZE_LARGE = 24;                     // 大きなフォントサイズ
    const int FONT_SIZE_SMALL = 18;                     // 小さなフォントサイズ

    const int boxWidth = screenWidth / 2 - BOX_WIDTH_OFFSET;
    const int leftPositionX = (screenWidth / 2 - boxWidth) / 2;
    const int leftPositionY = START_Y;

    if (currentPhase_ == SHOP_PHASE::SELECT_AMOUNT)
    {
        auto item = GetSelectedItem();

        if (item != nullptr)
        {
            const int AMOUNT_BOX_WIDTH = 300;           // 数量選択ボックスの幅
            const int AMOUNT_BOX_HEIGHT = 120;          // 数量選択ボックスの高さ
            const int BOX_MARGIN = 70;                  // 数量選択ボックスの余白
            const int BLEND_ALPHA = 200;                // 背景のアルファ値
            const int TEXT_OFFSET_X = 20;               // テキスト描画Xオフセット
            const int TEXT_OFFSET_Y_MAIN = 30;          // メインテキスト描画Yオフセット
            const int TEXT_OFFSET_Y_SUB = 70;           // サブテキスト描画Yオフセット

            int centerX = screenWidth / 2;
            int centerY = screenHeight / 2;

            int left = centerX - AMOUNT_BOX_WIDTH / 2;
            int top = centerY - AMOUNT_BOX_HEIGHT / 2;
            int right = centerX + AMOUNT_BOX_WIDTH / 2;
            int bottom = centerY + AMOUNT_BOX_HEIGHT / 2;

            SetDrawBlendMode(DX_BLENDMODE_ALPHA, BLEND_ALPHA);
            DrawBox(left - BOX_MARGIN, top, right + BOX_MARGIN, bottom, GetColor(0, 0, 0), true);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

            DrawBox(left - BOX_MARGIN, top, right + BOX_MARGIN, bottom, GetColor(255, 255, 255), false);

            std::string text = item->GetName() + " 数量: " + std::to_string(selectedQuantity_);
            Font::GetInstance().DrawDefaultText(
                left + TEXT_OFFSET_X,
                top + TEXT_OFFSET_Y_MAIN,
                text.c_str(),
                GetColor(255, 255, 0),
                FONT_SIZE_LARGE
            );

            std::string help = "↑↓: 数量変更  Enter: 決定";
            Font::GetInstance().DrawDefaultText(
                left + TEXT_OFFSET_X,
                top + TEXT_OFFSET_Y_SUB,
                help.c_str(),
                GetColor(200, 200, 200),
                FONT_SIZE_SMALL
            );
        }
        return;
    }

    const int MAIN_BOX_HEIGHT = 700;                    

    DrawBox(
        leftPositionX,
        leftPositionY,
        leftPositionX + boxWidth,
        leftPositionY + MAIN_BOX_HEIGHT,
        GetColor(30, 30, 30),
        true
    );
    DrawBox(
        leftPositionX,
        leftPositionY,
        leftPositionX + boxWidth,
        leftPositionY + MAIN_BOX_HEIGHT,
        GetColor(255, 255, 255),
        false
    );

    const int LIST_START_OFFSET = 10;                   // リスト描画開始の余白
    int startX = leftPositionX + LIST_START_OFFSET;
    int startY = leftPositionY + LIST_START_OFFSET;
    int totalItems = static_cast<int>(shopItems_.size());

    for (int i = 0; i < totalItems; ++i)
    {
        auto item = shopItems_[i];
        int row = i / SHOP_COLUMNS;
        int column = i % SHOP_COLUMNS;

        int positionX = startX + column * (SHOP_ITEM_WIDTH + SHOP_PADDING);
        int positionY = startY + row * (SHOP_ITEM_HEIGHT + SHOP_PADDING);

        bool isSelected = (currentArea_ == SHOP_AREA::ITEM_LIST && i == selectedItemIndex_);

        if (isSelected)
        {
            const int BORDER_MARGIN = 5;                // 選択枠のマージン
            const int BORDER_EXPAND_Y = 10;             // 選択枠の下方向拡張

            DrawBox(
                positionX - BORDER_MARGIN,
                positionY - BORDER_MARGIN,
                positionX + SHOP_ITEM_WIDTH + BORDER_MARGIN,
                positionY + SHOP_ITEM_HEIGHT + BORDER_EXPAND_Y,
                GetColor(255, 255, 0),
                false
            );
        }

        DrawGraph(positionX, positionY, item->GetImageHandle(), true);

        const int TEXT_OFFSET_Y_NAME = 2;               // 名前テキストのYオフセット
        const int TEXT_OFFSET_Y_QTY = 32;               // 数量テキストのYオフセット

        Font::GetInstance().DrawDefaultText(
            positionX,
            positionY + SHOP_ICON_SIZE + TEXT_OFFSET_Y_NAME,
            item->GetName().c_str(),
            GetColor(255, 255, 255),
            FONT_SIZE_LARGE
        );

        std::string quantityText = "x" + std::to_string(purchaseQuantities_[item->GetId()]);
        Font::GetInstance().DrawDefaultText(
            positionX,
            positionY + SHOP_ICON_SIZE + TEXT_OFFSET_Y_QTY,
            quantityText.c_str(),
            GetColor(200, 200, 0),
            FONT_SIZE_LARGE
        );
    }

    if (auto selectedItem = GetSelectedItem())
    {
        const std::string& description = selectedItem->GetDescription();

        const int DESC_BOX_OFFSET_Y = 200;              // 説明ボックスのYオフセット
        const int DESC_BOX_EXPAND_X = 300;              // 説明ボックスのX拡張
        const int DESC_BOX_EXPAND_Y_UP = 5;             // 説明ボックスの上方向拡張
        const int DESC_BOX_EXPAND_Y_DOWN = 200;         // 説明ボックスの下方向拡張
        const int TEXT_OFFSET_Y = 10;                   // テキストYオフセット

        int descriptionWidth = Font::GetInstance().GetDefaultTextWidth(description);
        int descriptionX = leftPositionX + (boxWidth - descriptionWidth) / 2;
        int descriptionY = leftPositionY + (Application::FULL_SCREEN_SIZE_Y / 2) + DESC_BOX_OFFSET_Y;

        DrawBox(
            descriptionX - DESC_BOX_EXPAND_X,
            descriptionY - DESC_BOX_EXPAND_Y_UP,
            descriptionX + descriptionWidth + DESC_BOX_EXPAND_X,
            descriptionY + DESC_BOX_EXPAND_Y_DOWN,
            GetColor(0, 0, 0),
            true
        );
        DrawBox(
            descriptionX - DESC_BOX_EXPAND_X,
            descriptionY - DESC_BOX_EXPAND_Y_UP,
            descriptionX + descriptionWidth + DESC_BOX_EXPAND_X,
            descriptionY + DESC_BOX_EXPAND_Y_DOWN,
            GetColor(255, 255, 255),
            false
        );

        Font::GetInstance().DrawDefaultText(
            descriptionX - DESC_BOX_EXPAND_X,
            descriptionY + TEXT_OFFSET_Y,
            description.c_str(),
            GetColor(255, 255, 255),
            FONT_SIZE_LARGE
        );
    }

    DrawRightSideUI();
}

void Shop::DrawRightSideUI(void)
{
    const int screenWidth = Application::SCREEN_SIZE_X;
    const int START_Y = 100;                            // 描画開始Y座標
    const int BOX_WIDTH_OFFSET = 100;                   // ボックス幅のオフセット
    const int MAIN_BOX_HEIGHT = 700;                    // メインリストボックスの高さ
    const int FONT_SIZE_DEFAULT = 24;                   // 標準フォントサイズ
    const int FONT_SIZE_HELP = 20;                      // ヘルプ用フォントサイズ

    const int boxWidth = screenWidth / 2 - BOX_WIDTH_OFFSET;
    const int rightPositionX = screenWidth / 2 + (screenWidth / 2 - boxWidth) / 2;

    DrawBox(
        rightPositionX,
        START_Y,
        rightPositionX + boxWidth,
        START_Y + MAIN_BOX_HEIGHT,
        GetColor(10, 10, 10),
        true
    );
    DrawBox(
        rightPositionX,
        START_Y,
        rightPositionX + boxWidth,
        START_Y + MAIN_BOX_HEIGHT,
        GetColor(255, 255, 255),
        false
    );

    const int ITEM_LIST_START_OFFSET_Y = 10;            // リスト開始Yオフセット
    const int ITEM_LINE_HEIGHT = 30;                    // 1行の高さ
    const int SELECT_BOX_MARGIN_X = 5;                  // 選択枠のマージンX
    const int SELECT_BOX_MARGIN_UP = 10;                // 選択枠の上マージン
    const int TEXT_OFFSET_X = 10;                       // テキスト左マージン

    int yOffset = ITEM_LIST_START_OFFSET_Y;
    int index = 0;
    int itemCount = 0;

    for (const auto& entry : purchaseQuantities_)
    {
        if (entry.second <= 0)
        {
            continue;
        }

        itemCount++;

        auto item = ItemManager::GetInstance().FindItemById(entry.first);

        if (item != nullptr)
        {
            int drawY = START_Y + yOffset + index * ITEM_LINE_HEIGHT;

            if (currentArea_ == SHOP_AREA::PURCHASE_LIST && purchaseListSelectedIndex_ == index)
            {
                DrawBox(
                    rightPositionX + SELECT_BOX_MARGIN_X,
                    drawY - SELECT_BOX_MARGIN_UP,
                    rightPositionX + boxWidth - SELECT_BOX_MARGIN_X,
                    drawY + ITEM_LINE_HEIGHT,
                    GetColor(255, 255, 0),
                    false
                );
            }

            std::string lineText = item->GetName() + " x" + std::to_string(entry.second)
                + "（" + std::to_string(item->GetPrice() * entry.second) + "G）";

            Font::GetInstance().DrawDefaultText(
                rightPositionX + TEXT_OFFSET_X,
                drawY,
                lineText.c_str(),
                0xffffff,
                FONT_SIZE_DEFAULT
            );

            index++;
        }
    }

    const int BUTTON_MARGIN_Y = 10;                     // 購入ボタンの上マージン
    int buttonPositionY = START_Y + yOffset + itemCount * ITEM_LINE_HEIGHT + BUTTON_MARGIN_Y;

    bool isButtonSelected = (currentArea_ == SHOP_AREA::PURCHASE_LIST) &&
        (purchaseListSelectedIndex_ == itemCount);

    if (isButtonSelected)
    {
        DrawBox(
            rightPositionX + SELECT_BOX_MARGIN_X,
            buttonPositionY - SELECT_BOX_MARGIN_UP,
            rightPositionX + boxWidth - SELECT_BOX_MARGIN_X,
            buttonPositionY + ITEM_LINE_HEIGHT,
            GetColor(255, 255, 0),
            false
        );
    }

    Font::GetInstance().DrawDefaultText(
        rightPositionX + TEXT_OFFSET_X,
        buttonPositionY,
        "[購入]",
        0xffffff,
        FONT_SIZE_DEFAULT
    );

    const int MONEY_INFO_Y = 600;                       // 所持金情報Y座標
    const int TOTAL_INFO_Y = 650;                       // 合計情報Y座標
    const int HELP_INFO_Y = 680;                        // ヘルプ情報Y座標

    int playerMoney = 0;
    if (player_ != nullptr)
    {
        playerMoney = player_->GetMoney();
    }

    int totalPrice = GetTotalPrice();

    Font::GetInstance().DrawDefaultText(
        rightPositionX + TEXT_OFFSET_X,
        START_Y + MONEY_INFO_Y,
        ("所持金: " + std::to_string(playerMoney) + " G").c_str(),
        0xffffff,
        FONT_SIZE_DEFAULT
    );
    Font::GetInstance().DrawDefaultText(
        rightPositionX + TEXT_OFFSET_X,
        START_Y + TOTAL_INFO_Y,
        ("合計: " + std::to_string(totalPrice) + " G").c_str(),
        GetColor(255, 200, 0),
        FONT_SIZE_DEFAULT
    );
    Font::GetInstance().DrawDefaultText(
        rightPositionX + TEXT_OFFSET_X,
        START_Y + HELP_INFO_Y,
        "[Tab] フォーカス切替 [Enter] 決定 [ESC] 閉じる",
        0xcccccc,
        FONT_SIZE_HELP
    );
}

std::shared_ptr<ItemBase> Shop::GetSelectedItem(void) const
{
    if (selectedItemIndex_ < 0 || selectedItemIndex_ >= static_cast<int>(shopItems_.size()))
    {
        return nullptr;
    }

    return shopItems_[selectedItemIndex_];
}

void Shop::ConfirmPurchase(void)
{
    int totalAmount = GetTotalPrice();

    if (player_ == nullptr || player_->GetMoney() < totalAmount)
    {
        return;
    }

    auto& itemManager = ItemManager::GetInstance();

    for (const auto& entry : purchaseQuantities_)
    {
        auto item = itemManager.FindItemById(entry.first);

        if (item != nullptr)
        {
            itemManager.AddQuantity(item, entry.second);
        }
    }

    player_->AddMoney(-totalAmount);
    purchaseQuantities_.clear();
    currentArea_ = SHOP_AREA::ITEM_LIST;
    purchaseListSelectedIndex_ = 0;
}

void Shop::RefreshDailyItems(void)
{
    shopItems_.clear();

    auto& itemManager = ItemManager::GetInstance();
    int seedCount = itemManager.GetSeedItemCount();

    for (int i = 0; i < seedCount; i++)
    {
        auto seedItem = itemManager.GetSeedItem(i);

        if (seedItem != nullptr)
        {
            shopItems_.push_back(seedItem);
        }
    }

    const int RANDOM_MIN = 0;                           // 乱数最小値
    const int RANDOM_MAX = 99;                          // 乱数最大値
    const int HERB_PROBABILITY = 10;                    // 薬草が出る確率（%）
    const int HERB_FIXED_PRICE = 1000;                  // 薬草の固定価格

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> distribution(RANDOM_MIN, RANDOM_MAX);

    if (distribution(generator) < HERB_PROBABILITY)
    {
        auto herbItem = itemManager.FindItemById("Herb");

        if (herbItem != nullptr)
        {
            herbItem->SetPrice(HERB_FIXED_PRICE);
            shopItems_.push_back(herbItem);
        }
    }
}