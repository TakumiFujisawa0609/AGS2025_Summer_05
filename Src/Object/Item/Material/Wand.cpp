#include "Wand.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int WAND_PRICE = 0;
}

Wand::Wand(void)
    : MaterialItem(
        "Wand",
        "ñ",
        "“S‚Å‚Å‚«‚½ñ‚ÌŒ´Œ^\n‚Ù‚©‚Ì‘fŞ‚Æ¬‚º‚Ä˜B‹à‚·‚é‚±‚Æ‚Å\n–{Ši“I‚Èñ‚ğ‚Â‚­‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::WAND).handleId_,
        WAND_PRICE
    )
{
}