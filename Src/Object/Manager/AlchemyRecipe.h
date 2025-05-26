#pragma once

#include <string>
#include <map>
#include <memory>

#include "../Item/Product/ProductItem.h"

class AlchemyRecipe
{
public:
	AlchemyRecipe(const std::map<std::string, int>& materials, std::shared_ptr<ProductItem> result);

	bool Match(const std::map<std::string, int>& selected) const;

	std::shared_ptr<ProductItem> GetResult(void) const;

private:
	std::map<std::string, int> requiredMaterials_;

	std::shared_ptr<ProductItem> result_;


};

