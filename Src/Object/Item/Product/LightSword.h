#pragma once

#include "ProductItem.h"

/// @brief ライトソードのクラス
class LightSword : public ProductItem
{
public:

    /// @brief コンストラクタ
    LightSword(void);

    /// @brief デストラクタ
    ~LightSword(void) override = default;
};