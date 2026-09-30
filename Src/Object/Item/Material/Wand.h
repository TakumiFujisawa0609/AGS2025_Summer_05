#pragma once

#include "MaterialItem.h"

/// @brief 杖のクラス
class Wand : public MaterialItem
{
public:

    /// @brief コンストラクタ
    Wand(void);

    /// @brief デストラクタ
    ~Wand(void) override = default;
};