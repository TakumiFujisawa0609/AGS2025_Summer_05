#include "WaterSword.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int SWORD_PRICE = 0;
}

WaterSword::WaterSword(void)
    : ProductItem(
        "WaterSword",
        "ウォーターソード",
        "水属性を宿した剣\n 材料\n ・水の魔石×２\n ・剣×1",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::WATER_SWORD).handleId_,
        SWORD_PRICE
    )
{
}