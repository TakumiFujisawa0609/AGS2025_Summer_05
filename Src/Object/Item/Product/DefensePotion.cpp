#include "DefensePotion.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int POTION_PRICE = 0;
}

DefensePotion::DefensePotion(void)
    : ProductItem(
        "DefensePotion",
        "硬化ポーソン",
        "飲むと一時的に防御力が高まる効果がある\n 材料\n ・麻痺草×２\n ・水×1",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::DEFENSE_POTION).handleId_,
        POTION_PRICE
    )
{
}