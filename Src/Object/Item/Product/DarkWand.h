#pragma once

#include "ProductItem.h"

/// @brief ダークワンドのクラス
class DarkWand : public ProductItem
{
public:

    /// @brief コンストラクタ
    DarkWand(void);

    /// @brief デストラクタ
    ~DarkWand(void) override = default;
};