#pragma once
#include "../ItemBase.h"

class ProductItem : public ItemBase
{
public:
    ProductItem(const std::string& name, const std::string& description, int quantity, int imageHandle)
    : ItemBase(name, description, quantity, imageHandle) {}

    virtual ITEM_TYPE GetItemType() const override { return ITEM_TYPE::PRODUCT; }
};


