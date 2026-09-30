#include "GaleHerb.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int HERB_PRICE = 0;
}

GaleHerb::GaleHerb(void)
    : MaterialItem(
        "GaleHerb",
        "風走草",
        "風の力を宿す不思議な草\n潰したエキスを摂取すると一時的に身体が軽くなる効果がある\n他の薬草をと混ぜるな危険",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::GALE_HERB).handleId_,
        HERB_PRICE
    )
{
}