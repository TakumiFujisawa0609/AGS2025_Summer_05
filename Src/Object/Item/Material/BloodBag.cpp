#include "BloodBag.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int BAG_PRICE = 0;
}

BloodBag::BloodBag(void)
    : MaterialItem(
        "BloodBag",
        "ŒŒ‘Ü",
        "‰½‚©‚ÌŒŒ‰t‚ª“ü‚Á‚Ä‚¢‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::BLOOD_BAG).handleId_,
        BAG_PRICE
    )
{
}