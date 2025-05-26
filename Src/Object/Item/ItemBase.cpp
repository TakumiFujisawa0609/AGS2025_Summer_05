#include "ItemBase.h"

ItemBase::ItemBase(const std::string& id, const std::string& name, const std::string& description, int quantity, int imageHandle)
{
    id_ = id;
	name_ = name;
	description_ = description;
	quantity_ = quantity;
    imageHandle_ = imageHandle;
}

const std::string& ItemBase::GetId(void) const
{
    return id_;
}

//–¼‘O‚Ìæ“¾
const std::string& ItemBase::GetName(void) const
{
    return name_;
}

//à–¾‚Ìæ“¾
const std::string& ItemBase::GetDescription(void) const 
{
    return description_;
}

int ItemBase::GetQuantity(void) const
{
    return quantity_;
}

int ItemBase::GetImageHandle() const 
{
    return imageHandle_;
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