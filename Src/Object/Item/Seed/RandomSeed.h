#pragma once

#include "SeedItem.h"

/// @brief ランダムな結果をもたらす特殊な種子クラス
class RandomSeed : public SeedItem
{
public:

    /// @brief コンストラクタ
    RandomSeed(void);

    /// @brief デストラクタ
    ~RandomSeed(void) override = default;
};