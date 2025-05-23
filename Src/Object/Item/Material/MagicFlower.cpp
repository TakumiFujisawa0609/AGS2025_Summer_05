#include "MagicFlower.h"

#include "../../../Manager/Generic/Resource.h"
#include "../../../Manager/Generic/ResourceManager.h"

MagicFlower::MagicFlower()
    : MaterialItem
    (
        "–‚—Í‘",
        "Ûæ‚·‚é‚±‚Æ‚Å–‚—Í‚ğ‘½­‚¾‚ª‰ñ•œ‚Å‚«‚é",
        0,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::MAGIC_FLOWER).handleId_
     )
{
}
