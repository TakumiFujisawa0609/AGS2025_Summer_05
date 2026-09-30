#include "AntiParalysisPotion.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int POTION_PRICE = 0;
}

AntiParalysisPotion::AntiParalysisPotion(void)
    : ProductItem(
        "AntiParalysisPotion",
        "解麻痺ポーソン",
        "飲むと麻痺の効力を中和する\n 材料\n ・麻痺草×２\n ・水×1",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::ANTIPARALYSIS_POTION).handleId_,
        POTION_PRICE
    )
{
}