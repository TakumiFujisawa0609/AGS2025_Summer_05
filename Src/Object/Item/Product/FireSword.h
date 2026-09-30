#pragma once

#include "ProductItem.h"

/// @brief フレイムソードのクラス
class FireSword : public ProductItem
{
public:

    /// @brief コンストラクタ
    FireSword(void);

    /// @brief デストラクタ
    ~FireSword(void) override = default;
};