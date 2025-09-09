#include "ItemBase.h"

ItemBase::ItemBase(const std::string& id, const std::string& name,
    const std::string& description, int quantity,
    int imageHandle, int price)
    : id_(id), name_(name), description_(description),
    imageHandle_(imageHandle), quantity_(quantity), price_(price)
{
}

const std::string& ItemBase::GetId(void) const
{
    return id_;
}

const std::string& ItemBase::GetName(void) const
{
    return name_;
}

const std::string& ItemBase::GetDescription(void) const
{
    return description_;
}

int ItemBase::GetQuantity(void) const
{
    return quantity_;
}

int ItemBase::GetImageHandle(void) const
{
    return imageHandle_;
}

int ItemBase::GetPrice(void) const
{
    return price_;
}

void ItemBase::SetPrice(int price)
{
    price_ = price;
}

void ItemBase::AddQuantity(int amount)
{
    quantity_ += amount;
}

void ItemBase::SubtractQuantity(int amount)
{
    quantity_ -= amount;
    if (quantity_ < 0) quantity_ = 0;
}
