#include "DarkSword.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int SWORD_PRICE = 0;
}

DarkSword::DarkSword(void)
    : ProductItem(
        "DarkSword",
        "ダークソード",
        "闇属性を宿した剣\n 材料\n ・闇の魔石×２\n ・剣×１",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::DARK_SWORD).handleId_,
        SWORD_PRICE
    )
{
}