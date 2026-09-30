#include "IceSword.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int SWORD_PRICE = 0;
}

IceSword::IceSword(void)
    : ProductItem(
        "IceSword",
        "アイスソード",
        "氷属性を宿した剣\n 材料\n ・氷の魔石×２\n ・剣×１",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::ICE_SWORD).handleId_,
        SWORD_PRICE
    )
{
}