#pragma once

#include "ProductItem.h"

/// @brief 解麻痺ポーションのクラス
class AntiParalysisPotion : public ProductItem
{
public:

    /// @brief コンストラクタ
    AntiParalysisPotion(void);

    /// @brief デストラクタ
    ~AntiParalysisPotion(void) override = default;
};