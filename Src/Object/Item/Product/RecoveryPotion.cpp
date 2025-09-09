#include "RecoveryPotion.h"

#include "../../../Manager/Generic/ResourceManager.h"

// コンストラクタ
RecoveryPotion::RecoveryPotion(void)
    : ProductItem
    (
        "RecoveryPotion",
        "回復ポーソン",
        "飲むと体力を回復する\n 材料\n ・薬草×２\n ・水×1",
        0,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::RECOVERY_POTION).handleId_,
        0
    )
{
}
