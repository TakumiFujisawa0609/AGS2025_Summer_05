#pragma once

#include "ProductItem.h"

/// @brief 魔力ポーションのクラス
class MagicPotion : public ProductItem
{
public:

    /// @brief コンストラクタ
    MagicPotion(void);

    /// @brief デストラクタ
    ~MagicPotion(void) override = default;
};