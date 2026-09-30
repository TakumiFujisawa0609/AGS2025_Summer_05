#include "FireWand.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int WAND_PRICE = 0;
}

FireWand::FireWand(void)
    : ProductItem(
        "FireWand",
        "ƒtƒŒƒCƒ€ƒƒ“ƒh",
        "‰Î‘®«‚ğh‚µ‚½ñ\n Ş—¿\n E‰Î‚Ì–‚Î~‚Q\n Eñ~‚P",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::FIRE_WAND).handleId_,
        WAND_PRICE
    )
{
}