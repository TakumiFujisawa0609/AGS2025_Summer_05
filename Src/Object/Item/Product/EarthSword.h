#pragma once

#include "ProductItem.h"

/// @brief アースソードのクラス
class EarthSword : public ProductItem
{
public:

    /// @brief コンストラクタ
    EarthSword(void);

    /// @brief デストラクタ
    ~EarthSword(void) override = default;
};