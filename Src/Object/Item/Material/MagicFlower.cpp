#include "MagicFlower.h"

#include "../../../Manager/Generic/ResourceManager.h"

MagicFlower::MagicFlower()
    : MaterialItem
    (
        "MagicFlower",
        "–‚—Í‘",
        "–‚—Í‚ğ‰ñ•œ‚·‚éŒø‰Ê‚ª‚ ‚é\n’×‚µ‚ÄƒGƒLƒX‚ğÛæ‚·‚é‚±‚Æ‚Å–‚—Í‚ğ‘½­‚¾‚ª‰ñ•œ‚Å‚«‚é\n‘¼‚Ì–ò‘‚ğ‚Æ¬‚º‚é‚ÈŠëŒ¯",
        0,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::MAGIC_FLOWER).handleId_,
        0
     )
{
}
