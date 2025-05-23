#include "ItemManager.h"

#include "../Item/Material/Herb.h"
#include "../Item/Material/AntidoteHerb.h"
#include "../Item/Material/MagicFlower.h"
#include "../Item/Material/Water.h"
#include "../Item/Product/RecoveryPotion.h"
#include "../Item/Product/AntidotePotion.h"
#include "../Item/Product/MagicPotion.h"

// シングルトンインスタンスの初期化
ItemManager* ItemManager::instance_ = nullptr;

// インスタンス生成（初回呼び出し時のみ）
void ItemManager::CreateInstance(void)
{
	if (!instance_)
	{
		instance_ = new ItemManager();
		instance_->Init();
	}
}

// インスタンス取得（既に生成されている前提）
ItemManager& ItemManager::GetInstance(void)
{
	return *instance_;
}

// 初期化処理：インベントリをクリアし、初期アイテムを追加する
void ItemManager::Init()
{
	// 全リストをクリア
	materialItems_.clear();
	productItems_.clear();

	// 素材アイテムを追加
	AddItem(std::make_shared<Herb>());
	AddItem(std::make_shared<AntidoteHerb>());
	AddItem(std::make_shared<MagicFlower>());
	AddItem(std::make_shared<Water>());

	// 完成品アイテムを追加（例：回復ポーション）
	AddItem(std::make_shared<RecoveryPotion>());
	AddItem(std::make_shared<AntidotePotion>());
	AddItem(std::make_shared<MagicPotion>());

	// 初期所持数設定（素材）
	AddQuantity(materialItems_[0], 5); // Herb
	AddQuantity(materialItems_[1], 5); // AntidoteHerb
	AddQuantity(materialItems_[2], 5); // MagicFlower

	// 完成品は所持0スタートでOK
}

// アイテムを追加（素材か完成品かを自動分類して保存）
void ItemManager::AddItem(std::shared_ptr<ItemBase> item)
{
	// 素材アイテムとしてキャスト可能か確認
	if (auto material = std::dynamic_pointer_cast<MaterialItem>(item))
	{
		materialItems_.push_back(material);
	}
	// 完成品アイテムとしてキャスト可能か確認
	else if (auto product = std::dynamic_pointer_cast<ProductItem>(item))
	{
		productItems_.push_back(product);
	}
}

// 素材アイテムを取得
std::shared_ptr<MaterialItem> ItemManager::GetMaterialItem(int index) const
{
	if (index >= 0 && index < materialItems_.size())
	{
		return materialItems_[index];
	}
	return nullptr;
}

// 完成品アイテムを取得
std::shared_ptr<ProductItem> ItemManager::GetProductItem(int index) const
{
	if (index >= 0 && index < productItems_.size())
	{
		return productItems_[index];
	}
	return nullptr;
}

// 素材アイテムの個数を取得
int ItemManager::GetMaterialItemCount(void) const
{
	return static_cast<int>(materialItems_.size());
}

// 完成品アイテムの個数を取得
int ItemManager::GetProductItemCount(void) const
{
	return static_cast<int>(productItems_.size());
}

// 所持数を増やす（素材または完成品を指定）
void ItemManager::AddQuantity(std::shared_ptr<ItemBase> item, int amount)
{
	if (item)
	{
		item->AddQuantity(amount);
	}
}

// 所持数を減らす（素材または完成品を指定）
void ItemManager::SubtractQuantity(std::shared_ptr<ItemBase> item, int amount)
{
	if (item)
	{
		item->SubtractQuantity(amount);
	}
}

// インスタンス破棄（メモリ解放）
void ItemManager::Destroy(void)
{
	delete instance_;
	instance_ = nullptr;
}
