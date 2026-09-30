#pragma once

#include "../ItemBase.h"

/// @brief 素材アイテムの基底クラス
class MaterialItem : public ItemBase
{
public:

    /// @brief コンストラクタ
    /// @param id アイテムID
    /// @param name アイテム名
    /// @param description アイテムの説明
    /// @param quantity 所持数
    /// @param imageHandle アイテム画像のハンドル
    /// @param price 価格
    MaterialItem(
        const std::string& id,
        const std::string& name,
        const std::string& description,
        int quantity,
        int imageHandle,
        int price
    );

    /// @brief デストラクタ
    ~MaterialItem(void) override = default;

    /// @brief アイテムの種別を取得する
    /// @return アイテムの種別（素材）
    ITEM_TYPE_MATERIAL GetItemType(void) const override;
};