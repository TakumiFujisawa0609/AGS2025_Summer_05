#pragma once

#include "MaterialItem.h"

/// @brief 鉄鉱石のクラス
class IronOre : public MaterialItem
{
public:

    /// @brief コンストラクタ
    IronOre(void);

    /// @brief デストラクタ
    ~IronOre(void) override = default;
};