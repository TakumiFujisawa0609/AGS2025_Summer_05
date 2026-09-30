#pragma once

#include "ProductItem.h"

/// @brief アイスワンドのクラス
class IceWand : public ProductItem
{
public:

    /// @brief コンストラクタ
    IceWand(void);

    /// @brief デストラクタ
    ~IceWand(void) override = default;
};