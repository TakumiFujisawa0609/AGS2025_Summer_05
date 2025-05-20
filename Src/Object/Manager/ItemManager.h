#pragma once

#include<vector>
#include<memory>

#include"../../Object/Item/ItemBase.h"

class ItemManager
{
public:

	ItemManager() = default;
	~ItemManager() = default;

	void Init();

	void AddItem(std::shared_ptr<ItemBase> item);

	std::shared_ptr<ItemBase> GetItem(int index) const;

	int GetItemCount(void) const;

	void AddQuantity(int index, int amount);

	void SubtractQuantity(int index, int amount);

private:
	std::vector<std::shared_ptr<ItemBase>> items_;
};

