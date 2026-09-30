#include "MaterialItem.h"

MaterialItem::MaterialItem(
    const std::string& id,
    const std::string& name,
    const std::string& description,
    int quantity,
    int imageHandle,
    int price)
    : ItemBase(id, name, description, quantity, imageHandle, price)
{
}

ITEM_TYPE_MATERIAL MaterialItem::GetItemType(void) const
{
    return ITEM_TYPE_MATERIAL::MATERIAL;
}