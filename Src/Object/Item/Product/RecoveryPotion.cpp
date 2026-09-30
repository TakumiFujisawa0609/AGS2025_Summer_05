#include "RecoveryPotion.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int POTION_PRICE = 0;
}

RecoveryPotion::RecoveryPotion(void)
    : ProductItem(
        "RecoveryPotion",
        "回復ポーソン",
        "飲むと体力を回復する\n 材料\n ・薬草×２\n ・水×1",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::RECOVERY_POTION).handleId_,
        POTION_PRICE
    )
{
}