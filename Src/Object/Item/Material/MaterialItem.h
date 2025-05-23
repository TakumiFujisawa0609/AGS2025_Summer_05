#pragma once

#include "../ItemBase.h"

class MaterialItem : public ItemBase
{
public:
    MaterialItem(const std::string& name, const std::string& description, int quantity, int imageHandle)
    : ItemBase(name, description, quantity, imageHandle) {};

    virtual ITEM_TYPE GetItemType(void) const override { return ITEM_TYPE::MATERIAL; }
};


