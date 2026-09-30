#pragma once

#include "ProductItem.h"

/// @brief 解毒ポーションのクラス
class AntidotePotion : public ProductItem
{
public:

    /// @brief コンストラクタ
    AntidotePotion(void);

    /// @brief デストラクタ
    ~AntidotePotion(void) override = default;
};