#pragma once

#include "ProductItem.h"

/// @brief 俊敏ポーションのクラス
class SpeedPotion : public ProductItem
{
public:

    /// @brief コンストラクタ
    SpeedPotion(void);

    /// @brief デストラクタ
    ~SpeedPotion(void) override = default;
};