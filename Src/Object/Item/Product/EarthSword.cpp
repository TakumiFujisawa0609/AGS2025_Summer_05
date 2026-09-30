#include "EarthSword.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int SWORD_PRICE = 0;
}

EarthSword::EarthSword(void)
    : ProductItem(
        "EarthSword",
        "ƒA[ƒXƒ\[ƒh",
        "“y‘®«‚ğh‚µ‚½Œ•\n Ş—¿\n E“y‚Ì–‚Î~‚Q\n Œ•~‚P",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::EARTH_SWORD).handleId_,
        SWORD_PRICE
    )
{
}