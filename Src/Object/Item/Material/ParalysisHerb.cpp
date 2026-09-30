#include "ParalysisHerb.h"
#include "../../../Manager/Generic/ResourceManager.h"

namespace
{
    const int INITIAL_QUANTITY = 0;
    const int HERB_PRICE = 0;
}

ParalysisHerb::ParalysisHerb(void)
    : MaterialItem(
        "ParalysisHerb",
        "麻痺草",
        "触れたものを麻痺させる不思議な草\n潰してエキスを水で薄めるなどすると麻痺効果を解く効果がある\n他の薬草をと混ぜるな危険",
        INITIAL_QUANTITY,
        ResourceManager::GetInstance().Load(ResourceManager::SRC::PARALYSIS_HERB).handleId_,
        HERB_PRICE
    )
{
}