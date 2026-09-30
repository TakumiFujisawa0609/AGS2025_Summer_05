#pragma once

#include "MaterialItem.h"

/// @brief 剣のクラス
class Sword : public MaterialItem
{
public:

    /// @brief コンストラクタ
    Sword(void);

    /// @brief デストラクタ
    ~Sword(void) override = default;
};