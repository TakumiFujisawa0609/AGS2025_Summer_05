#include "Speed​​Potion.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int POTION_PRICE = 0;
}

SpeedPotion::SpeedPotion(void)
    : ProductItem(
        "SpeedPotion",
        "俊敏ポーソン",
        "飲むと一時的に動きが早くなる効果がある\n 材料\n ・風走草×２\n ・水×1",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::SPEED_POTION).handleId_,
        POTION_PRICE
    )
{
}