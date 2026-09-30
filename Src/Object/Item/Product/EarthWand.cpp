#include "EarthWand.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int WAND_PRICE = 0;
}

EarthWand::EarthWand(void)
    : ProductItem(
        "EarthWand",
        "ƒA[ƒXƒƒ“ƒh",
        "“y‘®«‚ğh‚µ‚½ñ\n Ş—¿\n E“y‚Ì–‚Î~‚Q\n Eñ~‚P",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::EARTH_WAND).handleId_,
        WAND_PRICE
    )
{
}