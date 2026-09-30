#pragma once

#include "MaterialItem.h"

/// @brief 硬体草（素材アイテム）のクラス
class HardbodyHerb : public MaterialItem
{
public:

    /// @brief コンストラクタ
    HardbodyHerb(void);

    /// @brief デストラクタ
    ~HardbodyHerb(void) override = default;
};