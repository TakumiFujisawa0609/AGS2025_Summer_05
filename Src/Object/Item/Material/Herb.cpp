#include "Herb.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int HERB_PRICE = 1000;
}

Herb::Herb(void)
    : MaterialItem(
        "Herb",
        "–ò‘",
        "‘Ì‚ğ–ü‚·Œø‰Ê‚ª‚ ‚é\n’×‚µ‚ÄƒGƒLƒX‚È‚Ç‚ğ•‰‰ÓŠ‚É‚©‚¯‚é‚Æ¡‚è‚ª­‚µ‘‚­‚È‚é\n‘¼‚Ì–ò‘‚ğ‚Æ¬‚º‚é‚ÈŠëŒ¯",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::HERB).handleId_,
        HERB_PRICE
    )
{
}