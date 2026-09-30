#include "ItemManager.h"

#include "../Item/Material/Herb.h"
#include "../Item/Material/AntidoteHerb.h"
#include "../Item/Material/MagicFlower.h"
#include "../Item/Material/ParalysisHerb.h"
#include "../Item/Material/GaleHerb.h"
#include "../Item/Material/DemonPowerHerb.h"
#include "../Item/Material/HardbodyHerb.h"
#include "../Item/Material/Water.h"
#include "../Item/Material/IronOre.h"
#include "../Item/Material/FireMagicStone.h"
#include "../Item/Material/WaterMagicStone.h"
#include "../Item/Material/WindMagicStone.h"
#include "../Item/Material/EarthMagicStone.h"
#include "../Item/Material/IceMagicStone.h"
#include "../Item/Material/LightMagicStone.h"
#include "../Item/Material/DarkMagicStone.h"
#include "../Item/Material/Sword.h"
#include "../Item/Material/Wand.h"
#include "../Item/Product/RecoveryPotion.h"
#include "../Item/Product/AntidotePotion.h"
#include "../Item/Product/AntiParalysisPotion.h"
#include "../Item/Product/MagicPotion.h"
#include "../Item/Product/Speed​​Potion.h"
#include "../Item/Product/PowerPotion.h"
#include "../Item/Product/DefensePotion.h"
#include "../Item/Product/FireSword.h"
#include "../Item/Product/WaterSword.h"
#include "../Item/Product/WindSword.h"
#include "../Item/Product/EarthSword.h"
#include "../Item/Product/IceSword.h"
#include "../Item/Product/LightSword.h"
#include "../Item/Product/DarkSword.h"
#include "../Item/Product/FireWand.h"
#include "../Item/Product/WaterWand.h"
#include "../Item/Product/WindWand.h"
#include "../Item/Product/EarthWand.h"
#include "../Item/Product/IceWand.h"
#include "../Item/Product/LightWand.h"
#include "../Item/Product/DarkWand.h"
#include "../Item/Product/Garbage.h"
#include "../Item/Seed/RandomSeed.h"

ItemManager* ItemManager::instance_ = nullptr;

void ItemManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new ItemManager();
        instance_->Init();
    }
}

ItemManager& ItemManager::GetInstance(void)
{
    return *instance_;
}

void ItemManager::Init(void)
{
    materialItems_.clear();
    productItems_.clear();
    seedItems_.clear();
    allItems_.clear();
    idItemMap_.clear();

    Register(std::make_shared<Herb>());
    Register(std::make_shared<AntidoteHerb>());
    Register(std::make_shared<MagicFlower>());
    Register(std::make_shared<ParalysisHerb>());
    Register(std::make_shared<GaleHerb>());
    Register(std::make_shared<DemonPowerHerb>());
    Register(std::make_shared<HardbodyHerb>());
    Register(std::make_shared<Water>());
    Register(std::make_shared<IronOre>());
    Register(std::make_shared<FireMagicStone>());
    Register(std::make_shared<WaterMagicStone>());
    Register(std::make_shared<WindMagicStone>());
    Register(std::make_shared<EarthMagicStone>());
    Register(std::make_shared<IceMagicStone>());
    Register(std::make_shared<LightMagicStone>());
    Register(std::make_shared<DarkMagicStone>());
    Register(std::make_shared<Sword>());
    Register(std::make_shared<Wand>());

    Register(std::make_shared<RecoveryPotion>());
    Register(std::make_shared<AntidotePotion>());
    Register(std::make_shared<AntiParalysisPotion>());
    Register(std::make_shared<MagicPotion>());
    Register(std::make_shared<SpeedPotion>());
    Register(std::make_shared<PowerPotion>());
    Register(std::make_shared<DefensePotion>());
    Register(std::make_shared<FireSword>());
    Register(std::make_shared<WaterSword>());
    Register(std::make_shared<WindSword>());
    Register(std::make_shared<EarthSword>());
    Register(std::make_shared<IceSword>());
    Register(std::make_shared<LightSword>());
    Register(std::make_shared<DarkSword>());
    Register(std::make_shared<FireWand>());
    Register(std::make_shared<WaterWand>());
    Register(std::make_shared<WindWand>());
    Register(std::make_shared<EarthWand>());
    Register(std::make_shared<IceWand>());
    Register(std::make_shared<LightWand>());
    Register(std::make_shared<DarkWand>());
    Register(std::make_shared<Garbage>());

    Register(std::make_shared<RandomSeed>());

    for (auto& item : allItems_)
    {
        if (auto materialItem = std::dynamic_pointer_cast<MaterialItem>(item))
        {
            materialItems_.push_back(materialItem);
        }
        else if (auto productItem = std::dynamic_pointer_cast<ProductItem>(item))
        {
            productItems_.push_back(productItem);
        }
        else if (auto seedItem = std::dynamic_pointer_cast<SeedItem>(item))
        {
            seedItems_.push_back(seedItem);
        }
    }

    const int INITIAL_QUANTITY = 0;

    AddQuantity(FindItemById("Herb"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("AntidoteHerb"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("MagicFlower"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("ParalysisHerb"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("GaleHerb"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("DemonPowerHerb"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("HardbodyHerb"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("Water"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("IronOre"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("FireMagicStone"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("WaterMagicStone"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("WindMagicStone"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("EarthMagicStone"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("IceMagicStone"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("LightMagicStone"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("DarkMagicStone"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("Sword"), INITIAL_QUANTITY);
    AddQuantity(FindItemById("Wand"), INITIAL_QUANTITY);
}

void ItemManager::AddItem(std::shared_ptr<ItemBase> item)
{
    (void)item;
}

std::shared_ptr<MaterialItem> ItemManager::GetMaterialItem(int index) const
{
    const int MINIMUM_INDEX = 0;

    if (index >= MINIMUM_INDEX && index < static_cast<int>(materialItems_.size()))
    {
        return materialItems_[index];
    }

    return nullptr;
}

std::shared_ptr<ProductItem> ItemManager::GetProductItem(int index) const
{
    const int MINIMUM_INDEX = 0;

    if (index >= MINIMUM_INDEX && index < static_cast<int>(productItems_.size()))
    {
        return productItems_[index];
    }

    return nullptr;
}

std::shared_ptr<SeedItem> ItemManager::GetSeedItem(int index) const
{
    const int MINIMUM_INDEX = 0;

    if (index >= MINIMUM_INDEX && index < static_cast<int>(seedItems_.size()))
    {
        return seedItems_[index];
    }

    return nullptr;
}

int ItemManager::GetMaterialItemCount(void) const
{
    return static_cast<int>(materialItems_.size());
}

int ItemManager::GetProductItemCount(void) const
{
    return static_cast<int>(productItems_.size());
}

int ItemManager::GetSeedItemCount(void) const
{
    return static_cast<int>(seedItems_.size());
}

void ItemManager::AddQuantity(std::shared_ptr<ItemBase> item, int amount)
{
    if (item != nullptr)
    {
        item->AddQuantity(amount);

        for (auto& callback : quantityChangeCallbacks_)
        {
            callback(item->GetId(), amount);
        }
    }
}

void ItemManager::SubtractQuantity(std::shared_ptr<ItemBase> item, int amount)
{
    if (item != nullptr)
    {
        item->SubtractQuantity(amount);

        const int INVERT_MULTIPLIER = -1;

        for (auto& callback : quantityChangeCallbacks_)
        {
            callback(item->GetId(), amount * INVERT_MULTIPLIER);
        }
    }
}

void ItemManager::Register(std::shared_ptr<ItemBase> item)
{
    if (item != nullptr)
    {
        allItems_.push_back(item);
        idItemMap_[item->GetId()] = item;
    }
}

std::shared_ptr<ItemBase> ItemManager::FindItemById(const std::string& id)
{
    auto iterator = idItemMap_.find(id);

    if (iterator != idItemMap_.end())
    {
        return iterator->second;
    }

    return nullptr;
}

void ItemManager::RegisterQuantityChangeCallback(QuantityChangeCallback callback)
{
    quantityChangeCallbacks_.push_back(callback);
}

void ItemManager::Destroy(void)
{
    delete instance_;
    instance_ = nullptr;
}