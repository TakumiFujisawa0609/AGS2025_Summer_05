#pragma once

#include "MaterialItem.h"

/// @brief 水アイテムのクラス
class Water : public MaterialItem
{
public:

    /// @brief コンストラクタ
    Water(void);

    /// @brief デストラクタ
    ~Water(void) override = default;
};