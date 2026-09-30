#include "AntidoteHerb.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int HERB_PRICE = 0;
}

AntidoteHerb::AntidoteHerb(void)
    : MaterialItem(
        "AntidoteHerb",
        "解毒草",
        "毒を治すために使う薬草\n潰したエキスを摂取すると一時的に毒の効果を薄めることができる\n他の薬草をと混ぜるな危険",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::ANTIDOTE_HERB).handleId_,
        HERB_PRICE
    )
{
}