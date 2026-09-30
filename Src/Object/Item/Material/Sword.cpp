#include "Sword.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int SWORD_PRICE = 0;
}

Sword::Sword(void)
    : MaterialItem(
        "Sword",
        "Œ•",
        "“S‚Å‚Å‚«‚½Œ•‚ÌŒ´Œ^\n‚Ù‚©‚Ì‘fŞ‚Æ¬‚º‚Ä˜B‹à‚·‚é‚±‚Æ‚Å\n–{Ši“I‚ÈŒ•‚ğ‚Â‚­‚é‚±‚Æ‚ª‚Å‚«‚é",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::SWORD).handleId_,
        SWORD_PRICE
    )
{
}