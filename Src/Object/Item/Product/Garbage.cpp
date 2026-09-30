#include "Garbage.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int GARBAGE_PRICE = 0;
}

Garbage::Garbage(void)
    : ProductItem(
        "Garbage",
        "é∏îsÇÃçÏïi",
        "âΩÇ…Ç‡égÇ¶Ç»Ç¢Ç‡ÇÃ",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::GARBAGE).handleId_,
        GARBAGE_PRICE
    )
{
}