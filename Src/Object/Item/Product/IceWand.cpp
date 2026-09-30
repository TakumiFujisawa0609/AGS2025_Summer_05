#include "IceWand.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int WAND_PRICE = 0;
}

IceWand::IceWand(void)
    : ProductItem(
        "IceWand",
        "ƒAƒCƒXƒƒ“ƒh",
        "•X‘®«‚ğh‚µ‚½ñ\n Ş—¿\n E•X‚Ì–‚Î~‚Q\n Eñ~‚P",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::ICE_WAND).handleId_,
        WAND_PRICE
    )
{
}