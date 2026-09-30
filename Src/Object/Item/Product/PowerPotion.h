#pragma once

#include "ProductItem.h"

/// @brief 力のポーションのクラス
class PowerPotion : public ProductItem
{
public:

    /// @brief コンストラクタ
    PowerPotion(void);

    /// @brief デストラクタ
    ~PowerPotion(void) override = default;
};