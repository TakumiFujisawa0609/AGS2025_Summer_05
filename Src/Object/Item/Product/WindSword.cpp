#include "WindSword.h"

#include "../../../Manager/Generic/ResourceManager.h"

WindSword::WindSword(void)
	:ProductItem
	(
		"WindSword",
		"ウィンドソード",
		"風属性を宿した剣\n 材料\n ・風の魔石×２\n ・剣×1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WIND_SWORD).handleId_,
		0
	)
{
}
