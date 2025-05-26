#pragma once

#include<vector>
#include<memory>
#include<unordered_map>

#include"../../Object/Item/ItemBase.h"
#include"../../Object/Item/Material/MaterialItem.h"
#include"../../Object/Item/Product/ProductItem.h"

class ItemManager
{
public:

	//インスタンスの生成
	static void CreateInstance(void);

	//インスタンスの取得
	static ItemManager& GetInstance(void);

	~ItemManager() = default;

	void Init();

	// アイテムの追加（MaterialかProductかで自動分類）
	void AddItem(std::shared_ptr<ItemBase> item);

	// アイテム取得
	std::shared_ptr<MaterialItem> GetMaterialItem(int index) const;
	std::shared_ptr<ProductItem> GetProductItem(int index) const;

	// アイテム数取得
	int GetMaterialItemCount(void) const;
	int GetProductItemCount(void) const;

	// 所持数操作
	void AddQuantity(std::shared_ptr<ItemBase> item, int amount);
	void SubtractQuantity(std::shared_ptr<ItemBase> item, int amount);

	//名前の登録
	void Register(std::shared_ptr<ItemBase> item);

	//名前の取得
	std::shared_ptr<ItemBase> FindItemById(const std::string& id);

	static void Destroy(void);

private:

	ItemManager() = default;
	

	ItemManager(const ItemManager&) = delete;
	ItemManager& operator=(const ItemManager&) = delete;

	static ItemManager* instance_;

	std::vector<std::shared_ptr<MaterialItem>> materialItems_;
	std::vector<std::shared_ptr<ProductItem>> productItems_;
	std::vector<std::shared_ptr<ItemBase>> allItems_;
	std::unordered_map<std::string, std::shared_ptr<ItemBase>> idItemMap_;
};

