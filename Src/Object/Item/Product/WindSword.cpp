#include "WindSword.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int SWORD_PRICE = 0;
}

WindSword::WindSword(void)
    : ProductItem(
        "WindSword",
        "ウィンドソード",
        "風属性を宿した剣\n 材料\n ・風の魔石×２\n ・剣×1",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::WIND_SWORD).handleId_,
        SWORD_PRICE
    )
{
}