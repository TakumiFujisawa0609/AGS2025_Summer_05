#include "AntidoteHerb.h"

#include "../../../Manager/Generic/ResourceManager.h"

AntidoteHerb::AntidoteHerb()
    : MaterialItem(
        "AntidoteHerb",
        "解毒草",
        "毒を治すために使う薬草\n潰したエキスを摂取すると一時的に毒の効果を薄めることができる\n他の薬草をと混ぜるな危険",
        0,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::ANTIDOTE_HERB).handleId_,
        0
    )
{
}
