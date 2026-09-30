#include "WaterWand.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int WAND_PRICE = 0;
}

WaterWand::WaterWand(void)
    : ProductItem(
        "WaterWand",
        "ウォーターワンド",
        "水属性を宿した杖\n 材料\n ・水の魔石×２\n ・杖×１",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::WATER_WAND).handleId_,
        WAND_PRICE
    )
{
}