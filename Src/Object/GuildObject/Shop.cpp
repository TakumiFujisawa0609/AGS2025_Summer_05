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

Shop::~Shop(void) {}

void Shop::SetPlayer(std::shared_ptr<Player> player)
{
    player_ = player;
}

void Shop::SetDateTimeManager(DateTimeManager* dt)
{
    dateTimeManager_ = dt;
}

int Shop::GetPrice(std::shared_ptr<ItemBase> item) const
{
    return item ? item->GetPrice() : 0;
}

int Shop::GetTotalPrice(void) const
{
    int total = 0;
    for (const auto& entry : purchaseQuantities_)
    {
        auto item = ItemManager::GetInstance().FindItemById(entry.first);
        if (item)
        {
            total += item->GetPrice() * entry.second;
        }
    }
    return total;
}

int Shop::GetSelectedQuantity(void) const
{
    auto item = GetSelectedItem();
    if (!item) return 0;
    auto it = purchaseQuantities_.find(item->GetId());
    return (it != purchaseQuantities_.end()) ? it->second : 0;
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

void Shop::Update()
{
    if (!isVisible_) return;

    auto& input = InputManager::GetInstance();
    auto& sound = SoundManager::GetInstance();

    // 日替わり更新
    if (dateTimeManager_)
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
            int row = selectedItemIndex_ / SHOP_COLUMNS;
            int col = selectedItemIndex_ % SHOP_COLUMNS;

            if (input.IsTrgDown(KEY_INPUT_LEFT))
            {
                sound.Play(SoundManager::SOUND::SE_SELECT);
                if (col > 0) selectedItemIndex_--;
            }
            else if (input.IsTrgDown(KEY_INPUT_RIGHT))
            {
                sound.Play(SoundManager::SOUND::SE_SELECT);
                if (col < SHOP_COLUMNS - 1 && selectedItemIndex_ + 1 < totalItems)
                    selectedItemIndex_++;
            }

            if (input.IsTrgDown(KEY_INPUT_RETURN))
            {
                sound.Play(SoundManager::SOUND::SE_PUSH);
                currentPhase_ = SHOP_PHASE::SELECT_AMOUNT;
                selectedQuantity_ = GetSelectedQuantity();
                if (selectedQuantity_ <= 0) selectedQuantity_ = 1;
            }

            if (input.IsTrgDown(KEY_INPUT_ESCAPE))
            {
                sound.Play(SoundManager::SOUND::SE_CANCEL);
                Hide();
                PlayerStop::GetInstance().ResumeMovement();
            }

            if (input.IsTrgDown(KEY_INPUT_TAB))
            {
                sound.Play(SoundManager::SOUND::SE_PUSH);
                currentArea_ = SHOP_AREA::PURCHASE_LIST;
                purchaseListSelectedIndex_ = 0;
            }
        }
        else // PURCHASE_LIST
        {
            int itemCount = 0;
            for (const auto& entry : purchaseQuantities_)
                if (entry.second > 0) itemCount++;

            int listSize = itemCount + 1; // +1 は購入ボタン

            if (input.IsTrgDown(KEY_INPUT_UP))
            {
                sound.Play(SoundManager::SOUND::SE_SELECT);
                purchaseListSelectedIndex_ = (purchaseListSelectedIndex_ - 1 + listSize) % listSize;
            }
            else if (input.IsTrgDown(KEY_INPUT_DOWN))
            {
                sound.Play(SoundManager::SOUND::SE_SELECT);
                purchaseListSelectedIndex_ = (purchaseListSelectedIndex_ + 1) % listSize;
            }

            if (purchaseListSelectedIndex_ < itemCount)
            {
                auto it = std::next(purchaseQuantities_.begin(), purchaseListSelectedIndex_);
                if (input.IsTrgDown(KEY_INPUT_LEFT) && it->second > 1)
                {
                    sound.Play(SoundManager::SOUND::SE_SELECT);
                    it->second--;
                }
                else if (input.IsTrgDown(KEY_INPUT_RIGHT))
                {
                    sound.Play(SoundManager::SOUND::SE_SELECT);
                    it->second++;
                }

            }
            else
            {
                if (input.IsTrgDown(KEY_INPUT_RETURN))
                {
                    sound.Play(SoundManager::SOUND::SE_PUSH);
                    ConfirmPurchase();
                    purchaseListSelectedIndex_ = 0;
                }
            }

            if (input.IsTrgDown(KEY_INPUT_ESCAPE))
            {
                sound.Play(SoundManager::SOUND::SE_CANCEL);
                Hide();
            }

            if (input.IsTrgDown(KEY_INPUT_TAB))
            {
                sound.Play(SoundManager::SOUND::SE_PUSH);
                currentArea_ = SHOP_AREA::ITEM_LIST;
            }
        }
        break;
    }
    case SHOP_PHASE::SELECT_AMOUNT:
    {
        if (input.IsTrgDown(KEY_INPUT_UP))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            selectedQuantity_++;
        }
        else if (input.IsTrgDown(KEY_INPUT_DOWN))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            if (selectedQuantity_ > 1) selectedQuantity_--;
        }

        if (input.IsTrgDown(KEY_INPUT_RETURN))
        {
            sound.Play(SoundManager::SOUND::SE_PUSH);
            auto item = GetSelectedItem();
            if (item)
            {
                purchaseQuantities_[item->GetId()] = selectedQuantity_;
            }
            currentPhase_ = SHOP_PHASE::SELECT_ITEM;
            currentArea_ = SHOP_AREA::PURCHASE_LIST;
            purchaseListSelectedIndex_ = 0;
        }

        if (input.IsTrgDown(KEY_INPUT_ESCAPE))
        {
            sound.Play(SoundManager::SOUND::SE_CANCEL);
            currentPhase_ = SHOP_PHASE::SELECT_ITEM;
        }
        break;
    }
    }
}

void Shop::Draw(void)
{
    if (!isVisible_) return;

    PlayerStop::GetInstance().StopMovement();

    const int screenWidth = Application::SCREEN_SIZE_X;
    const int screenHeight = Application::SCREEN_SIZE_Y;

    const int boxWidth = screenWidth / 2 - 100;
    const int leftX = (screenWidth / 2 - boxWidth) / 2;
    const int leftY = 100;
    const int fontSize = 24;

    if (currentPhase_ == SHOP_PHASE::SELECT_AMOUNT)
    {
        auto item = GetSelectedItem();
        if (item)
        {
            int centerX = screenWidth / 2;
            int centerY = screenHeight / 2;
            int boxWidth = 300;
            int boxHeight = 120;
            int left = centerX - boxWidth / 2;
            int top = centerY - boxHeight / 2;
            int right = centerX + boxWidth / 2;
            int bottom = centerY + boxHeight / 2;

            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
            DrawBox(left - 70, top, right + 70, bottom, GetColor(0, 0, 0), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

            DrawBox(left - 70, top, right + 70, bottom, GetColor(255, 255, 255), FALSE);

            std::string text = item->GetName() + " 数量: " + std::to_string(selectedQuantity_);
            Font::GetInstance().DrawDefaultText(left + 20, top + 30, text.c_str(), GetColor(255, 255, 0), 24);

            std::string help = "↑↓: 数量変更  Enter: 決定";
            Font::GetInstance().DrawDefaultText(left + 20, top + 70, help.c_str(), GetColor(200, 200, 200), 18);
        }
        return;
    }

    // 左側ショップ画面描画
    DrawBox(leftX, leftY, leftX + boxWidth, leftY + 700, GetColor(30, 30, 30), TRUE);
    DrawBox(leftX, leftY, leftX + boxWidth, leftY + 700, GetColor(255, 255, 255), FALSE);

    int startX = leftX + 10;
    int startY = leftY + 10;
    int totalItems = static_cast<int>(shopItems_.size());
    int itemsPerRow = SHOP_COLUMNS;

    for (int i = 0; i < totalItems; ++i)
    {
        auto item = shopItems_[i];
        int row = i / itemsPerRow;
        int col = i % itemsPerRow;

        int x = startX + col * (SHOP_ITEM_WIDTH + SHOP_PADDING);
        int y = startY + row * (SHOP_ITEM_HEIGHT + SHOP_PADDING);

        bool selected = (currentArea_ == SHOP_AREA::ITEM_LIST && i == selectedItemIndex_);
        if (selected)
        {
            DrawBox(x - 5, y - 5, x + SHOP_ITEM_WIDTH + 5, y + SHOP_ITEM_HEIGHT + 10, GetColor(255, 255, 0), FALSE);
        }

        DrawGraph(x, y, item->GetImageHandle(), TRUE);
        Font::GetInstance().DrawDefaultText(x, y + SHOP_ICON_SIZE + 2, item->GetName().c_str(), GetColor(255, 255, 255), 24);

        std::string quantityText = "x" + std::to_string(purchaseQuantities_[item->GetId()]);
        Font::GetInstance().DrawDefaultText(x, y + SHOP_ICON_SIZE + 32, quantityText.c_str(), GetColor(200, 200, 0), 24);
    }

    if (auto selected = GetSelectedItem())
    {
        const std::string& desc = selected->GetDescription();
        int descWidth = Font::GetInstance().GetDefaultTextWidth(desc);
        int descX = leftX + (boxWidth - descWidth) / 2;
        int descY = leftY + (Application::DEFA_SCREEN_SZIE_Y / 2) + 200;

        DrawBox(descX - 300, descY - 5, descX + descWidth + 300, descY + 200, GetColor(0, 0, 0), TRUE);
        DrawBox(descX - 300, descY - 5, descX + descWidth + 300, descY + 200, GetColor(255, 255, 255), false);

        Font::GetInstance().DrawDefaultText(descX - 300, descY + 10, desc.c_str(), GetColor(255, 255, 255), fontSize);
    }

    DrawRightSideUI();
}

void Shop::DrawRightSideUI()
{
    const int screenWidth = Application::SCREEN_SIZE_X;
    const int leftY = 100;
    const int boxWidth = screenWidth / 2 - 100;
    const int rightX = screenWidth / 2 + (screenWidth / 2 - boxWidth) / 2;

    DrawBox(rightX, leftY, rightX + boxWidth, leftY + 700, GetColor(10, 10, 10), TRUE);
    DrawBox(rightX, leftY, rightX + boxWidth, leftY + 700, GetColor(255, 255, 255), FALSE);

    int yOffset = 10;
    int index = 0;
    int itemCount = 0;

    for (const auto& entry : purchaseQuantities_)
    {
        if (entry.second <= 0) continue;
        itemCount++;

        auto item = ItemManager::GetInstance().FindItemById(entry.first);
        if (item)
        {
            int y = leftY + yOffset + index * 30;

            if (currentArea_ == SHOP_AREA::PURCHASE_LIST && purchaseListSelectedIndex_ == index)
            {
                DrawBox(rightX + 5, y - 10, rightX + boxWidth - 5, y + 30, GetColor(255, 255, 0), FALSE);
            }

            std::string line = item->GetName() + " x" + std::to_string(entry.second)
                + "（" + std::to_string(item->GetPrice() * entry.second) + "G）";

            Font::GetInstance().DrawDefaultText(rightX + 10, y, line.c_str(), 0xffffff, 24);
            index++;
        }
    }

    // 「購入」ボタン描画
    int buttonY = leftY + yOffset + itemCount * 30 + 10;
    bool isSelected = (currentArea_ == SHOP_AREA::PURCHASE_LIST) && (purchaseListSelectedIndex_ == itemCount);
    if (isSelected)
    {
        DrawBox(rightX + 5, buttonY - 10, rightX + boxWidth - 5, buttonY + 30, GetColor(255, 255, 0), FALSE);
    }
    Font::GetInstance().DrawDefaultText(rightX + 10, buttonY, "[購入]", 0xffffff, 24);

    int playerMoney = player_ ? player_->GetMoney() : 0;
    int totalPrice = GetTotalPrice();

    Font::GetInstance().DrawDefaultText(rightX + 10, leftY + 600, ("所持金: " + std::to_string(playerMoney) + " G").c_str(), 0xffffff, 24);
    Font::GetInstance().DrawDefaultText(rightX + 10, leftY + 650, ("合計: " + std::to_string(totalPrice) + " G").c_str(), GetColor(255, 200, 0), 24);
    Font::GetInstance().DrawDefaultText(rightX + 10, leftY + 680, "[Tab] フォーカス切替 [Enter] 決定 [ESC] 閉じる", 0xcccccc, 20);
}

std::shared_ptr<ItemBase> Shop::GetSelectedItem(void) const
{
    if (selectedItemIndex_ < 0 || selectedItemIndex_ >= static_cast<int>(shopItems_.size()))
        return nullptr;
    return shopItems_[selectedItemIndex_];
}

void Shop::ConfirmPurchase(void)
{
    int total = GetTotalPrice();
    if (!player_ || player_->GetMoney() < total)
        return;

    auto& itemManager = ItemManager::GetInstance();

    for (const auto& entry : purchaseQuantities_)
    {
        auto item = itemManager.FindItemById(entry.first);
        if (item)
        {
            itemManager.AddQuantity(item, entry.second);
        }
    }

    player_->AddMoney(-total);
    purchaseQuantities_.clear();
    currentArea_ = SHOP_AREA::ITEM_LIST;
    purchaseListSelectedIndex_ = 0;
}

void Shop::RefreshDailyItems(void)
{
    shopItems_.clear();

    auto& itemManager = ItemManager::GetInstance();
    int seedCount = itemManager.GetSeedItemCount();

    // 通常の種アイテム
    for (int i = 0; i < seedCount; i++)
    {
        auto seed = itemManager.GetSeedItem(i);
        if (seed)
        {
            shopItems_.push_back(seed);
        }
    }

    // --- 日替わり薬草（10%抽選） ---
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, 99);

    if (dist(rng) < 10)
    {
        auto herb = itemManager.FindItemById("Herb"); // 薬草
        if (herb)
        {
            herb->SetPrice(1000); // 固定価格
            shopItems_.push_back(herb);
        }
    }
}
