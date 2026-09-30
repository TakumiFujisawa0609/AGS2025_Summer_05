#pragma once

#include "ProductItem.h"

/// @brief 失敗作のクラス
class Garbage : public ProductItem
{
public:

    /// @brief コンストラクタ
    Garbage(void);

    /// @brief デストラクタ
    ~Garbage(void) override = default;
};