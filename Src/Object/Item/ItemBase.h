#pragma once

#include <string>

/// <summary>
/// アイテムの種別
/// </summary>
enum class ITEM_TYPE
{
    //種子
    SEED,

    //素材
    MATERIAL,

    //完成品
    PRODUCT,
};

/// <summary>
/// すべてのアイテムの基底クラス
/// </summary>
class ItemBase
{
public:
    // コンストラクタ
    ItemBase(const std::string& id, const std::string& name, const std::string& description,
        int quantity, int imageHandle, int price);

    // デストラクタ（仮想）
    virtual ~ItemBase(void) = default;

    // ID取得
    const std::string& GetId(void) const;

    // 名前を取得
    const std::string& GetName(void) const;

    // 説明を取得
    const std::string& GetDescription(void) const;

    // 所持数を取得
    int GetQuantity(void) const;

    // 画像ハンドルを取得
    int GetImageHandle(void) const;

    // 価格を取得
    int GetPrice(void) const;

    // 価格を設定
    void SetPrice(int price);

    // 所持数を増やす
    void AddQuantity(int amount);

    // 所持数を減らす（0未満にならない）
    void SubtractQuantity(int amount);

    // 種別を取得（Seed, Material, Product）
    virtual ITEM_TYPE GetItemType(void) const = 0;

protected:
    std::string id_;             // ID
    std::string name_;           // アイテム名
    std::string description_;    // アイテムの説明
    int imageHandle_;            // アイテム画像
    int quantity_;               // 所持数
    int price_;                  // 価格
};
