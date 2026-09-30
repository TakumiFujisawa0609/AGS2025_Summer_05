#pragma once

#include "MaterialItem.h"

/// @brief 解毒草のクラス
class AntidoteHerb : public MaterialItem
{
public:

    /// @brief コンストラクタ
    AntidoteHerb(void);

    /// @brief デストラクタ
    ~AntidoteHerb(void) override = default;
};