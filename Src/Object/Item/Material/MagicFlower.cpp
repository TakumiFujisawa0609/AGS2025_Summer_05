#include "MagicFlower.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int FLOWER_PRICE = 0;
}

MagicFlower::MagicFlower(void)
    : MaterialItem(
        "MagicFlower",
        "–‚—Í‘",
        "–‚—Í‚ğ‰ñ•œ‚·‚éŒø‰Ê‚ª‚ ‚é\n’×‚µ‚ÄƒGƒLƒX‚ğÛæ‚·‚é‚±‚Æ‚Å–‚—Í‚ğ‘½­‚¾‚ª‰ñ•œ‚Å‚«‚é\n‘¼‚Ì–ò‘‚ğ‚Æ¬‚º‚é‚ÈŠëŒ¯",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::MAGIC_FLOWER).handleId_,
        FLOWER_PRICE
    )
{
}