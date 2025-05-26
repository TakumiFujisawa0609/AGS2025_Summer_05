#include "AlchemyRecipe.h"

AlchemyRecipe::AlchemyRecipe(const std::map<std::string, int>& materials, std::shared_ptr<ProductItem> result)
{
	requiredMaterials_ = materials;

	result_ = result;
}

bool AlchemyRecipe::Match(const std::map<std::string, int>& selected) const
{
	for (const auto& req : requiredMaterials_)
	{
		auto it = selected.find(req.first);
		if (it == selected.end() || it->second < req.second)
		{
			return false;
		}
	}
	return true;
}

std::shared_ptr<ProductItem> AlchemyRecipe::GetResult(void) const
{
	return result_;
}


