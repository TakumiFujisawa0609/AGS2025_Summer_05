#include "IceMagicStone.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int STONE_PRICE = 0;
}

IceMagicStone::IceMagicStone(void)
    : MaterialItem(
        "IceMagicStone",
        "•X‚Ì–‚Î",
        "•X‘®«‚ğh‚·–‚Î\n•Ší‚ğì‚éÛ‚É•X‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::ICE_MAGIC_STONE).handleId_,
        STONE_PRICE
    )
{
}