#include "DemonPowerHerb.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int HERB_PRICE = 0;
}

DemonPowerHerb::DemonPowerHerb(void)
    : MaterialItem(
        "DemonPowerHerb",
        "鬼力草",
        "鬼と似たような力を得る薬草\n潰したエキスを摂取すると一時的に力を高める効果がある\n他の薬草をと混ぜるな危険",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::DEMON_POWER_HERB).handleId_,
        HERB_PRICE
    )
{
}