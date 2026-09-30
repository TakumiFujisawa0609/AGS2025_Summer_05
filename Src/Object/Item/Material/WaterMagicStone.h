#pragma once

#include "MaterialItem.h"

/// @brief 水の魔石のクラス
class WaterMagicStone : public MaterialItem
{
public:

    /// @brief コンストラクタ
    WaterMagicStone(void);

    /// @brief デストラクタ
    ~WaterMagicStone(void) override = default;
};