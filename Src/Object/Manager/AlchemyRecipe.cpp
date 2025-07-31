#include "AlchemyRecipe.h"

AlchemyRecipe::AlchemyRecipe(const std::map<std::string, int>& materials, std::shared_ptr<ItemBase> result)
    : requiredMaterials_(materials), result_(result)
{
}

bool AlchemyRecipe::Match(const std::map<std::string, int>& selected) const
{
    return selected == requiredMaterials_;
}

std::shared_ptr<ItemBase> AlchemyRecipe::GetResult(void) const
{
    return result_;
}

const std::map<std::string, int>& AlchemyRecipe::GetMaterials(void) const
{
    return requiredMaterials_;
}
