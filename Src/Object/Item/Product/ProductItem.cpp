#include "ProductItem.h"

ProductItem::ProductItem(
    const std::string& id,
    const std::string& name,
    const std::string& description,
    int quantity,
    int imageHandle,
    int price)
    : ItemBase(id, name, description, quantity, imageHandle, price)
{
}

ITEM_TYPE_MATERIAL ProductItem::GetItemType(void) const
{
    return ITEM_TYPE_MATERIAL::PRODUCT;
}