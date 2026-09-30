#pragma once

#include "ProductItem.h"

/// @brief 硬化ポーションのクラス
class DefensePotion : public ProductItem
{
public:

    /// @brief コンストラクタ
    DefensePotion(void);

    /// @brief デストラクタ
    ~DefensePotion(void) override = default;
};