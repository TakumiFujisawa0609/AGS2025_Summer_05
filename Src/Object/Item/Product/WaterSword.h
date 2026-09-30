#pragma once

#include "ProductItem.h"

/// @brief ウォーターソードのクラス
class WaterSword : public ProductItem
{
public:

    /// @brief コンストラクタ
    WaterSword(void);

    /// @brief デストラクタ
    ~WaterSword(void) override = default;
};