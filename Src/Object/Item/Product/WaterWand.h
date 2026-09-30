#pragma once

#include "ProductItem.h"

/// @brief ウォーターワンドのクラス
class WaterWand : public ProductItem
{
public:

    /// @brief コンストラクタ
    WaterWand(void);

    /// @brief デストラクタ
    ~WaterWand(void) override = default;
};