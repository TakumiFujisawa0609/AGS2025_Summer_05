#include "AntidotePotion.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int POTION_PRICE = 0;
}

AntidotePotion::AntidotePotion(void)
    : ProductItem(
        "AntidotePotion",
        "‰ğ“Åƒ|[ƒ\ƒ“",
        "ˆù‚Ş‚Æ“Å‚ÌŒø—Í‚ğ’†˜a‚·‚é\n Ş—¿\n E‰ğ“Å‘~‚Q\n E…~‚P",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::ANTIDOTE_POTION).handleId_,
        POTION_PRICE
    )
{
}