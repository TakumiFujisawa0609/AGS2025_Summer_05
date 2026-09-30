#include "DarkMagicStone.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int STONE_PRICE = 0;
}

DarkMagicStone::DarkMagicStone(void)
    : MaterialItem(
        "DarkMagicStone",
        "ˆÅ‚Ì–‚Î",
        "ˆÅ‘®«‚ğh‚µ‚½–‚Î\n•Ší‚ğì‚éÛ‚ÉˆÅ‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::DARK_MAGIC_STONE).handleId_,
        STONE_PRICE
    )
{
}