#include "WindMagicStone.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int STONE_PRICE = 0;
}

WindMagicStone::WindMagicStone(void)
    : MaterialItem(
        "WindMagicStone",
        "•—‚Ì–‚Î",
        "•—‘®«‚ğh‚µ‚½–‚Î\n•Ší‚ğì‚éÛ‚É•—‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::WIND_MAGIC_STONE).handleId_,
        STONE_PRICE
    )
{
}