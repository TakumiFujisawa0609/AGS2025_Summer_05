#pragma once

#include "MaterialItem.h"

/// @brief 光の魔石のクラス
class LightMagicStone : public MaterialItem
{
public:

    /// @brief コンストラクタ
    LightMagicStone(void);

    /// @brief デストラクタ
    ~LightMagicStone(void) override = default;
};