#include "MagicPotion.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int POTION_PRICE = 0;
}

MagicPotion::MagicPotion(void)
    : ProductItem(
        "MagicPotion",
        "魔力ポーソン",
        "飲むと魔力を回復する\n 材料\n ・魔力草×２\n ・水×1",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::MAGIC_POTION).handleId_,
        POTION_PRICE
    )
{
}