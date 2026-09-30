#pragma once

#include "ProductItem.h"

/// @brief ウィンドソードのクラス
class WindSword : public ProductItem
{
public:

    /// @brief コンストラクタ
    WindSword(void);

    /// @brief デストラクタ
    ~WindSword(void) override = default;
};