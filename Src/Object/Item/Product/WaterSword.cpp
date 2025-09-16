#include "WaterSword.h"

#include "../../../Manager/Generic/ResourceManager.h"

WaterSword::WaterSword(void)
	:ProductItem
	(
		"WaterSword",
		"ウォーターソード",
		"水属性を宿した剣\n 材料\n ・水の魔石×２\n ・剣×1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WATER_SWORD).handleId_,
		0
	)
{
}
