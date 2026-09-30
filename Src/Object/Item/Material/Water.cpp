#include "Water.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int WATER_PRICE = 0;
}

Water::Water(void)
    : MaterialItem(
        "Water",
        "êÖ",
        "êVëNÇ»êÖÅAópÇ∆ÇÕÇ¢ÇÎÇ¢ÇÎÇ†ÇÈÇÊ",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::WATER).handleId_,
        WATER_PRICE
    )
{
}