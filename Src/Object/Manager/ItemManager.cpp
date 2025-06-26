#include "ItemManager.h"

#include "../Item/Material/Herb.h"
#include "../Item/Material/AntidoteHerb.h"
#include "../Item/Material/MagicFlower.h"
#include "../Item/Material/Water.h"
#include "../Item/Product/RecoveryPotion.h"
#include "../Item/Product/AntidotePotion.h"
#include "../Item/Product/MagicPotion.h"
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
    Register(std::make_shared<Water>());

    // アイテム生成＆登録（完成品）
    Register(std::make_shared<RecoveryPotion>());
    Register(std::make_shared<AntidotePotion>());
    Register(std::make_shared<MagicPotion>());
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
    AddQuantity(FindItemById("Herb"), 50); // HerbのIDが0なら
    AddQuantity(FindItemById("AntidoteHerb"), 50); // AntidoteHerbのIDが1なら
    AddQuantity(FindItemById("MagicFlower"), 50); // MagicFlowerのIDが2なら
    AddQuantity(FindItemById("Water"), 50); // WaterのIDが3なら

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
    if (item) item->AddQuantity(amount);
}

void ItemManager::SubtractQuantity(std::shared_ptr<ItemBase> item, int amount)
{
    if (item) item->SubtractQuantity(amount);
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

void ItemManager::Destroy(void)
{
    delete instance_;
    instance_ = nullptr;
}
