#pragma once

#include "ProductItem.h"

/// @brief アイスソードのクラス
class IceSword : public ProductItem
{
public:

    /// @brief コンストラクタ
    IceSword(void);

    /// @brief デストラクタ
    ~IceSword(void) override = default;
};