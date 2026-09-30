#include "LightSword.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int SWORD_PRICE = 0;
}

LightSword::LightSword(void)
    : ProductItem(
        "LightSword",
        "ライトソード",
        "光属性を宿した剣\n 材料\n ・光の魔石×２\n ・剣×１",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::LIGHT_SWORD).handleId_,
        SWORD_PRICE
    )
{
}