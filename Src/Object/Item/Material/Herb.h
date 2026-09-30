#pragma once

#include "MaterialItem.h"

/// @brief 薬草アイテムのクラス
class Herb : public MaterialItem
{
public:

    /// @brief コンストラクタ
    Herb(void);

    /// @brief デストラクタ
    ~Herb(void) override = default;
};