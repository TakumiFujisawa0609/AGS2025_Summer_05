#pragma once

#include "ProductItem.h"

/// @brief アースワンドのクラス
class EarthWand : public ProductItem
{
public:

    /// @brief コンストラクタ
    EarthWand(void);

    /// @brief デストラクタ
    ~EarthWand(void) override = default;
};