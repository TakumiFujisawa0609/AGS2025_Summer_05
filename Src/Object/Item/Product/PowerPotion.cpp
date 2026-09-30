#include "PowerPotion.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int POTION_PRICE = 0;
}

PowerPotion::PowerPotion(void)
    : ProductItem(
        "PowerPotion",
        "力のポーソン",
        "飲むと一時的に力が高まる効果がある\n 材料\n ・鬼力草×２\n ・水×1",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::POWER_POTION).handleId_,
        POTION_PRICE
    )
{
}