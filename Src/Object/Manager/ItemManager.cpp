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


// シングルトンインスタンスの初期化
ItemManager* ItemManager::instance_ = nullptr;

void ItemManager::CreateInstance(void)
{
    if (!instance_)
    {
        instance_ = new ItemManager();
        instance_->Init();
    }
}

ItemManager& ItemManager::GetInstance(void)
{
    return *instance_;
}

void ItemManager::Init()
{
    materialItems_.clear();
    productItems_.clear();
    allItems_.clear();
    idItemMap_.clear();

    // アイテム生成＆登録（素材）
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

    // アイテム生成＆登録（完成品）
    Register(std::make_shared<RecoveryPotion>());
    Register(std::make_shared<AntidotePotion>());
    Register(std::make_shared<AntiParalysisPotion>());
    Register(std::make_shared<MagicPotion>());
    Register(std::make_shared<Speed​​Potion>());
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

    //アイテム生成＆登録(種子)
    Register(std::make_shared<RandomSeed>());


    // allItems_に登録されたアイテムからカテゴリ別に振り分け
    for (auto& item : allItems_)
    {
        if (auto material = std::dynamic_pointer_cast<MaterialItem>(item))
        {
            materialItems_.push_back(material);
        }
        else if (auto product = std::dynamic_pointer_cast<ProductItem>(item))
        {
            productItems_.push_back(product);
        }
        else if (auto seed = std::dynamic_pointer_cast<SeedItem>(item))
        {
            seedItems_.push_back(seed);
        }
    }

    // 初期所持数設定（例）
    AddQuantity(FindItemById("Herb"), 0); 
    AddQuantity(FindItemById("AntidoteHerb"), 0);
    AddQuantity(FindItemById("MagicFlower"), 0);
    AddQuantity(FindItemById("ParalysisHerb"), 0);
    AddQuantity(FindItemById("GaleHerb"), 0);
    AddQuantity(FindItemById("DemonPowerHerb"), 0); 
    AddQuantity(FindItemById("HardbodyHerb"), 0);
    AddQuantity(FindItemById("Water"), 0); 
    AddQuantity(FindItemById("IronOre"), 0);
    AddQuantity(FindItemById("FireMagicStone"), 0);
    AddQuantity(FindItemById("WaterMagicStone"), 0);
    AddQuantity(FindItemById("WindMagicStone"), 0);
    AddQuantity(FindItemById("EarthMagicStone"), 0);
    AddQuantity(FindItemById("IceMagicStone"), 0);
    AddQuantity(FindItemById("LightMagicStone"), 0);
    AddQuantity(FindItemById("DarkMagicStone"), 0);
    AddQuantity(FindItemById("Sword"), 0);
    AddQuantity(FindItemById("Wand"), 0);

    // 完成品は0スタート
}

void ItemManager::AddItem(std::shared_ptr<ItemBase> item)
{

}

std::shared_ptr<MaterialItem> ItemManager::GetMaterialItem(int index) const
{
    if (index >= 0 && index < (int)materialItems_.size())
        return materialItems_[index];
    return nullptr;
}

std::shared_ptr<ProductItem> ItemManager::GetProductItem(int index) const
{
    if (index >= 0 && index < (int)productItems_.size())
        return productItems_[index];
    return nullptr;
}

std::shared_ptr<SeedItem> ItemManager::GetSeedItem(int index) const
{
    if (index >= 0 && index < (int)seedItems_.size())
        return seedItems_[index];
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
    if (item)
    {
        item->AddQuantity(amount);

        // コールバック呼び出し
        for (auto& cb : quantityChangeCallbacks_)
        {
            cb(item->GetId(), amount);
        }
    }
}

void ItemManager::SubtractQuantity(std::shared_ptr<ItemBase> item, int amount)
{
    if (item)
    {
        item->SubtractQuantity(amount);

        // コールバック呼び出し（減った量はマイナス値で通知）
        for (auto& cb : quantityChangeCallbacks_)
        {
            cb(item->GetId(), -amount);
        }
    }
}

void ItemManager::Register(std::shared_ptr<ItemBase> item)
{
    allItems_.push_back(item);
    idItemMap_[item->GetId()] = item;
}

std::shared_ptr<ItemBase> ItemManager::FindItemById(const std::string& id)
{
    auto it = idItemMap_.find(id);
    if (it != idItemMap_.end())
        return it->second;
    return nullptr;
}

void ItemManager::RegisterQuantityChangeCallback(QuantityChangeCallback cb)
{
    quantityChangeCallbacks_.push_back(cb);
}

void ItemManager::Destroy(void)
{
    delete instance_;
    instance_ = nullptr;
}
