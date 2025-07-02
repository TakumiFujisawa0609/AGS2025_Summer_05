#pragma once

#include "../ItemBase.h"

class SeedItem : public ItemBase
{
public:
	SeedItem(const std::string& id, const std::string& name, const std::string& description, int quantity, int imageHandle, int price)
		:ItemBase(id, name, description, quantity, imageHandle), price_(price) {};

	virtual ITEM_TYPE GetItemType(void) const override { return ITEM_TYPE::SEED; }

	int GetPrice(void) const { return price_; }

private:
	int price_;
};

