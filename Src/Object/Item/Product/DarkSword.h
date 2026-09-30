#pragma once

#include "ProductItem.h"

/// @brief ダークソードのクラス
class DarkSword : public ProductItem
{
public:

    /// @brief コンストラクタ
    DarkSword(void);

    /// @brief デストラクタ
    ~DarkSword(void) override = default;
};