#pragma once

#include "ProductItem.h"

/// @brief フレイムワンドのクラス
class FireWand : public ProductItem
{
public:

    /// @brief コンストラクタ
    FireWand(void);

    /// @brief デストラクタ
    ~FireWand(void) override = default;
};