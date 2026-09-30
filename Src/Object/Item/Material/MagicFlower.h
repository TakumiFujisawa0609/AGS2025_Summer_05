#pragma once

#include "MaterialItem.h"

/// @brief 魔力草のクラス
class MagicFlower : public MaterialItem
{
public:

    /// @brief コンストラクタ
    MagicFlower(void);

    /// @brief デストラクタ
    ~MagicFlower(void) override = default;
};