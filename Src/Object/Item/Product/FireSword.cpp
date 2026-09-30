#include "FireSword.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int SWORD_PRICE = 0;
}

FireSword::FireSword(void)
    : ProductItem(
        "FireSword",
        "フレイムソード",
        "火属性を宿した剣\n 材料\n ・火の魔石×２\n ・剣×1",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::FIRE_SWORD).handleId_,
        SWORD_PRICE
    )
{
}