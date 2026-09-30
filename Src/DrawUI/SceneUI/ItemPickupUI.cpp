#include "ItemPickupUI.h"

#include <DxLib.h>

#include "../Font.h"
#include "../../Object/Manager/ItemManager.h"
#include "../../Application.h"

ItemPickupUI::ItemPickupUI(void)
{
    pickups_.clear();
}

ItemPickupUI::~ItemPickupUI(void)
{
}

void ItemPickupUI::Init(void)
{
    ItemManager::GetInstance().RegisterQuantityChangeCallback(
        [this](const std::string& itemId, int delta)
        {
            if (delta > 0)
            {
                auto item = ItemManager::GetInstance().FindItemById(itemId);
                if (item)
                {
                    AddPickup(item->GetName(), delta);
                }
            }
        }
    );
}

void ItemPickupUI::Update(void)
{
    for (auto iterator = pickups_.begin(); iterator != pickups_.end(); )
    {
        iterator->timer--;
        if (iterator->timer <= 0)
        {
            iterator = pickups_.erase(iterator);
        }
        else
        {
            ++iterator;
        }
    }
}

void ItemPickupUI::Draw(void)
{
    auto& font = Font::GetInstance();
    int startPositionY = Application::FULL_SCREEN_SIZE_Y / 2; 

    for (size_t index = 0; index < pickups_.size(); ++index)
    {
        const auto& pickupInfo = pickups_[index];
        std::string text = pickupInfo.itemName + " ~" + 
            std::to_string(pickupInfo.quantity) + " “üŽèI";

        font.DrawDefaultText(DRAW_START_POSITION_X, startPositionY 
            + static_cast<int>(index * DRAW_LINE_HEIGHT),
            text.c_str(), COLOR_WHITE, FONT_SIZE, Font::FONT_TYPE_ANTIALIASING_EDGE);
    }
}

void ItemPickupUI::AddPickup(const std::string& itemName, int quantity)
{
    for (auto& pickupInfo : pickups_)
    {
        if (pickupInfo.itemName == itemName)
        {
            pickupInfo.quantity += quantity;
            pickupInfo.timer = DISPLAY_TIME;
            return;
        }
    }

    pickups_.push_back({ itemName, quantity, DISPLAY_TIME });
}