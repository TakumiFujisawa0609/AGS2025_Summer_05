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
	for (auto it = pickups_.begin(); it != pickups_.end(); )
	{
		it->timer--;
		if (it->timer <= 0)
			it = pickups_.erase(it);
		else
			++it;
	}
}

void ItemPickupUI::Draw(void)
{
	auto& font = Font::GetInstance();
	int startX = 0;
	int startY = Application::DEFA_SCREEN_SZIE_Y / 2;
	int lineHeight = 30;

	for (size_t i = 0; i < pickups_.size(); ++i)
	{
		const auto& p = pickups_[i];
		std::string text = p.itemName + " ×" + std::to_string(p.quantity) + " 入手！";

		font.DrawDefaultText(startX, startY + static_cast<int>(i * lineHeight),
			text.c_str(), GetColor(255, 255, 255), 18, Font::FONT_TYPE_ANTIALIASING_EDGE);
	}
}

void ItemPickupUI::AddPickup(const std::string& itemName, int quantity)
{
	// すでに表示中のものはまとめる
	for (auto& p : pickups_)
	{
		if (p.itemName == itemName)
		{
			p.quantity += quantity;
			p.timer = DISPLAY_TIME; // 再表示
			return;
		}
	}

	// 新規追加
	pickups_.push_back({ itemName, quantity, DISPLAY_TIME });
}
