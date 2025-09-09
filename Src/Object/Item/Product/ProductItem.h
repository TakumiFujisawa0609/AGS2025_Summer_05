#pragma once
#include "../ItemBase.h"

class ProductItem : public ItemBase
{
public:
    ProductItem(const std::string& id, const std::string& name, const std::string& description, int quantity, int imageHandle, int price)
    : ItemBase(id, name, description, quantity, imageHandle, price) {}

    virtual ITEM_TYPE GetItemType() const override { return ITEM_TYPE::PRODUCT; }
};


