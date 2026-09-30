#pragma once

#include <string>

/// @brief アイテムの種別を定義する列挙型
enum class ITEM_TYPE_MATERIAL
{
    SEED,       // 種子
    MATERIAL,   // 素材
    PRODUCT,    // 完成品
};

/// @brief すべてのアイテムの基底クラス
class ItemBase
{
public:

    /// @brief コンストラクタ
    /// @param id アイテムID
    /// @param name アイテム名
    /// @param description アイテムの説明
    /// @param quantity 所持数
    /// @param imageHandle アイテム画像のハンドル
    /// @param price 価格
    ItemBase(
        const std::string& id,
        const std::string& name,
        const std::string& description,
        int quantity,
        int imageHandle,
        int price
    );

    /// @brief デストラクタ
    virtual ~ItemBase(void) = default;

    /// @brief IDを取得する
    /// @return ID文字列
    const std::string& GetId(void) const;

    /// @brief 名前を取得する
    /// @return アイテム名
    const std::string& GetName(void) const;

    /// @brief 説明を取得する
    /// @return アイテムの説明
    const std::string& GetDescription(void) const;

    /// @brief 所持数を取得する
    /// @return 現在の所持数
    int GetQuantity(void) const;

    /// @brief 画像ハンドルを取得する
    /// @return 画像ハンドルID
    int GetImageHandle(void) const;

    /// @brief 価格を取得する
    /// @return 価格
    int GetPrice(void) const;

    /// @brief 価格を設定する
    /// @param price 設定する価格
    void SetPrice(int price);

    /// @brief 所持数を増やす
    /// @param amount 増やす量
    void AddQuantity(int amount);

    /// @brief 所持数を減らす
    /// @param amount 減らす量
    void SubtractQuantity(int amount);

    /// @brief アイテムの種別を取得する
    /// @return アイテムの種別
    virtual ITEM_TYPE_MATERIAL GetItemType(void) const;

protected:

    // アイテム基本情報関連
    std::string id_;          // ID
    std::string name_;        // アイテム名
    std::string description_; // アイテムの説明
    int imageHandle_;         // アイテム画像
    int quantity_;            // 所持数
    int price_;               // 価格
};