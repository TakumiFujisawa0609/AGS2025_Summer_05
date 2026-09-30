#include "EarthMagicStone.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int STONE_PRICE = 0;
}

EarthMagicStone::EarthMagicStone(void)
    : MaterialItem(
        "EarthMagicStone",
        "“y‚Ì–‚Î",
        "“y‘®«‚ğh‚µ‚½–‚Î\n•Ší‚ğì‚éÛ‚É“y‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::EARTH_MAGIC_STONE).handleId_,
        STONE_PRICE
    )
{
}