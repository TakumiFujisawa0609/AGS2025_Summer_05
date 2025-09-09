#include "AntiParalysisPotion.h"

#include "../../../Manager/Generic/ResourceManager.h"

AntiParalysisPotion::AntiParalysisPotion(void)
	:ProductItem
	(
		"AntiParalysisPotion",
		"解麻痺ポーソン",
		"飲むと麻痺の効力を中和する\n 材料\n ・麻痺草×２\n ・水×1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ANTIPARALYSIS_POTION).handleId_,
		0
	)
{
}
