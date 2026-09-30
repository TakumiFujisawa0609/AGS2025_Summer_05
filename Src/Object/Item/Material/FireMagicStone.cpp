#include "FireMagicStone.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int STONE_PRICE = 0;
}

FireMagicStone::FireMagicStone(void)
    : MaterialItem(
        "FireMagicStone",
        "‰Î‚Ì–‚Î",
        "‰Î‘®«‚ğh‚·–‚Î\n•Ší‚ğì‚éÛ‚É‰Î‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::FIRE_MAGIC_STONE).handleId_,
        STONE_PRICE
    )
{
}