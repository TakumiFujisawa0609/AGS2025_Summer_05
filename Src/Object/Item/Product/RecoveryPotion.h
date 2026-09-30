#pragma once

#include "ProductItem.h"

/// @brief 回復ポーションのクラス
class RecoveryPotion : public ProductItem
{
public:

    /// @brief コンストラクタ
    RecoveryPotion(void);

    /// @brief デストラクタ
    ~RecoveryPotion(void) override = default;
};