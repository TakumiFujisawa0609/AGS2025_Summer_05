#include "RecoveryPotion.h"

#include "../../../Manager/Generic/Resource.h"
#include "../../../Manager/Generic/ResourceManager.h"

// コンストラクタ
RecoveryPotion::RecoveryPotion(void)
    : ProductItem
    (
        "回復ポーソン",
        "飲むと体力を回復する",
        0,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::RECOVERY_POTION).handleId_
    )
{
}
