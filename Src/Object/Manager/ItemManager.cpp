#include "ItemManager.h"

#include "../Item/Herb.h"
#include"../Item/AntidoteHerb.h"

void ItemManager::Init() 
{
	// ‰ŠúŠƒAƒCƒeƒ€‚ğ“o˜^
	AddItem(std::make_shared<Herb>());
	AddItem(std::make_shared<AntidoteHerb>());
}

void ItemManager::AddItem(std::shared_ptr<ItemBase> item)
{
	items_.push_back(item);
}

std::shared_ptr<ItemBase> ItemManager::GetItem(int index) const
{
	return (index >= 0 && index < items_.size()) ? items_[index] : nullptr;
}

int ItemManager::GetItemCount(void) const
{
	return static_cast<int>(items_.size());
}

void ItemManager::AddQuantity(int index, int amount)
{
	if (auto item = GetItem(index))
	{
		item->AddQuantity(amount);
	}
}

void ItemManager::SubtractQuantity(int index, int amount)
{
	if (auto item = GetItem(index))
	{
		item->SubtractQuantity(amount);
	}
}


