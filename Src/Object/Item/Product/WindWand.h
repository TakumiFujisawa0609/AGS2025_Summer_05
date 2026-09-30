#pragma once

#include "ProductItem.h"

/// @brief ウィンドワンドのクラス
class WindWand : public ProductItem
{
public:

    /// @brief コンストラクタ
    WindWand(void);

    /// @brief デストラクタ
    ~WindWand(void) override = default;
};