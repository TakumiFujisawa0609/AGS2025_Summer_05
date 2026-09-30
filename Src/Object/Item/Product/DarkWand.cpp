#include "DarkWand.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int WAND_PRICE = 0;
}

DarkWand::DarkWand(void)
    : ProductItem(
        "DarkWand",
        "ƒ_[ƒNƒƒ“ƒh",
        "ˆÅ‘®«‚ğh‚µ‚½ñ\n Ş—¿\n EˆÅ‚Ì–‚Î~‚Q\n Eñ~‚P",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::DARK_WAND).handleId_,
        WAND_PRICE
    )
{
}