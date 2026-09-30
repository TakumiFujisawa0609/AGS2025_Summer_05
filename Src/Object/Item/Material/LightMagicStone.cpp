#include "LightMagicStone.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int STONE_PRICE = 0;
}

LightMagicStone::LightMagicStone(void)
    : MaterialItem(
        "LightMagicStone",
        "Œõ‚Ì–‚Î",
        "Œõ‘®«‚ğh‚µ‚½–‚Î\n•Ší‚ğì‚éÛ‚ÉŒõ‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::LIGHT_MAGIC_STONE).handleId_,
        STONE_PRICE
    )
{
}