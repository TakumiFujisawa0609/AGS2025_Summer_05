#include "LightWand.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int WAND_PRICE = 0;
}

LightWand::LightWand(void)
    : ProductItem(
        "LightWand",
        "ƒ‰ƒCƒgƒƒ“ƒh",
        "Œõ‘®«‚ğh‚µ‚½ñ\n Ş—¿\n EŒõ‚Ì–‚Î~‚Q\n Eñ~‚P",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::LIGHT_WAND).handleId_,
        WAND_PRICE
    )
{
}