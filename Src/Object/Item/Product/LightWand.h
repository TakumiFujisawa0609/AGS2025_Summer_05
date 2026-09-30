#pragma once

#include "ProductItem.h"

/// @brief ライトワンドのクラス
class LightWand : public ProductItem
{
public:

    /// @brief コンストラクタ
    LightWand(void);

    /// @brief デストラクタ
    ~LightWand(void) override = default;
};