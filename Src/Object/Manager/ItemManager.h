#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <unordered_map>

#include "../../Object/Item/ItemBase.h"
#include "../../Object/Item/Material/MaterialItem.h"
#include "../../Object/Item/Product/ProductItem.h"
#include "../../Object/Item/Seed/SeedItem.h"

/// @brief アイテムの所持数変更時に呼び出されるコールバック関数の型定義
using QuantityChangeCallback = std::function<void(const std::string& itemId, int delta)>;

/// @brief すべてのアイテムの管理・統括を行うシングルトンクラス
class ItemManager
{
public:

    /// @brief インスタンスを生成する
    static void CreateInstance(void);

    /// @brief インスタンスを取得する
    /// @return ItemManagerのインスタンス参照
    static ItemManager& GetInstance(void);

    /// @brief デストラクタ
    ~ItemManager(void) = default;

    /// @brief 初期化処理
    void Init(void);

    /// @brief アイテムを追加する
    /// @param item 追加するアイテムのshared_ptr
    void AddItem(std::shared_ptr<ItemBase> item);

    /// @brief 素材アイテムを取得する
    /// @param index 取得するインデックス
    /// @return 素材アイテムのshared_ptr（範囲外の場合はnullptr）
    std::shared_ptr<MaterialItem> GetMaterialItem(int index) const;

    /// @brief 完成品アイテムを取得する
    /// @param index 取得するインデックス
    /// @return 完成品アイテムのshared_ptr（範囲外の場合はnullptr）
    std::shared_ptr<ProductItem> GetProductItem(int index) const;

    /// @brief 種子アイテムを取得する
    /// @param index 取得するインデックス
    /// @return 種子アイテムのshared_ptr（範囲外の場合はnullptr）
    std::shared_ptr<SeedItem> GetSeedItem(int index) const;

    /// @brief 素材アイテムの総数を取得する
    /// @return 素材アイテムの数
    int GetMaterialItemCount(void) const;

    /// @brief 完成品アイテムの総数を取得する
    /// @return 完成品アイテムの数
    int GetProductItemCount(void) const;

    /// @brief 種子アイテムの総数を取得する
    /// @return 種子アイテムの数
    int GetSeedItemCount(void) const;

    /// @brief アイテムの所持数を増やす
    /// @param item 対象のアイテム
    /// @param amount 増やす数量
    void AddQuantity(std::shared_ptr<ItemBase> item, int amount);

    /// @brief アイテムの所持数を減らす
    /// @param item 対象のアイテム
    /// @param amount 減らす数量
    void SubtractQuantity(std::shared_ptr<ItemBase> item, int amount);

    /// @brief アイテムをマネージャーに登録する
    /// @param item 登録するアイテム
    void Register(std::shared_ptr<ItemBase> item);

    /// @brief IDからアイテムを検索する
    /// @param id アイテムID
    /// @return 見つかったアイテム
    std::shared_ptr<ItemBase> FindItemById(const std::string& id);

    /// @brief 所持数変更コールバックを登録する
    /// @param callback 登録するコールバック関数
    void RegisterQuantityChangeCallback(QuantityChangeCallback callback);

    /// @brief インスタンスを破棄する
    static void Destroy(void);

private:

    /// @brief コンストラクタ
    ItemManager(void) = default;

    /// @brief コピーコンストラクタ（使用禁止）
    ItemManager(const ItemManager&) = delete;

    /// @brief 代入演算子（使用禁止）
    ItemManager& operator=(const ItemManager&) = delete;

    // 静的インスタンス関連
    static ItemManager* instance_;

    // アイテムコレクション関連
    std::vector<std::shared_ptr<SeedItem>> seedItems_;
    std::vector<std::shared_ptr<MaterialItem>> materialItems_;
    std::vector<std::shared_ptr<ProductItem>> productItems_;
    std::vector<std::shared_ptr<ItemBase>> allItems_;
    std::unordered_map<std::string, std::shared_ptr<ItemBase>> idItemMap_;
    std::vector<QuantityChangeCallback> quantityChangeCallbacks_;
};