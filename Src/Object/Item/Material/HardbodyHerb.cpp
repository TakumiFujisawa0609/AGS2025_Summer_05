#include "HardbodyHerb.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int HERB_PRICE = 0;
}

HardbodyHerb::HardbodyHerb(void)
    : MaterialItem(
        "HardbodyHerb",
        "硬体草",
        "体を硬くする効果がある薬草\n潰したエキスを水で薄めて摂取すると一時的に身体が硬くなる効果がある\n他の薬草をと混ぜるな危険",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::HARD_BODY_HERB).handleId_,
        HERB_PRICE
    )
{
}