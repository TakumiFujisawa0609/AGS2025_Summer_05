#include "WaterMagicStone.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int STONE_PRICE = 0;
}

WaterMagicStone::WaterMagicStone(void)
    : MaterialItem(
        "WaterMagicStone",
        "…‚Ì–‚Î",
        "…‘®«‚ğh‚·–‚Î\n•Ší‚ğì‚éÛ‚É…‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::WATER_MAGIC_STONE).handleId_,
        STONE_PRICE
    )
{
}