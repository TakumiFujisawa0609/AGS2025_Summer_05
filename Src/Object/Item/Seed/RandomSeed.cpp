#include "RandomSeed.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int SEED_PRICE = 100;
}

RandomSeed::RandomSeed(void)
    : SeedItem(
        "RandomSeed",
        "ŽíŽq",
        "“ÁŽê‚ÈŽíŽq‚È‚É‚ªŽæ‚ê‚é‚©‚Í‰^‚µ‚¾‚¢",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::SEED).handleId_,
        SEED_PRICE
    )
{
}