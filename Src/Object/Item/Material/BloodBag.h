#pragma once

#include "MaterialItem.h"

/// @brief 血袋のクラス
class BloodBag : public MaterialItem
{
public:

    /// @brief コンストラクタ
    BloodBag(void);

    /// @brief デストラクタ
    ~BloodBag(void) override = default;
};