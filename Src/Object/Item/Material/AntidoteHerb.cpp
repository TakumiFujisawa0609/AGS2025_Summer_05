#include "AntidoteHerb.h"

#include "../../../Manager/Generic/ResourceManager.h"

AntidoteHerb::AntidoteHerb()
    : MaterialItem(
        "AntidoteHerb",
        "解毒草",
        "毒を治すために使う薬草。毒状態の時に効果的。",
        0,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::ANTIDOTE_HERB).handleId_
    )
{
}
