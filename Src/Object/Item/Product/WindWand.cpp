#include "WindWand.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int WAND_PRICE = 0;
}

WindWand::WindWand(void)
    : ProductItem(
        "WindWand",
        "ƒEƒBƒ“ƒhƒƒ“ƒh",
        "•—‘®«‚ğh‚µ‚½ñ\n Ş—¿\n E•—‚Ì–‚Î~‚Q\n Eñ~‚P",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::WIND_WAND).handleId_,
        WAND_PRICE
    )
{
}