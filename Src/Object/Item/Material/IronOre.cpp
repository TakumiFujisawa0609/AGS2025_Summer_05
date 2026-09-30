#include "IronOre.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int ORE_PRICE = 0;
}

IronOre::IronOre(void)
    : MaterialItem(
        "IronOre",
        "“SzÎ",
        "“S‚ÌzÎ\nŒ•‚ÌŒ´Œ^‚âAñ‚ÌŒ´Œ^‚ğì‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::IRON_ORE).handleId_,
        ORE_PRICE
    )
{
}