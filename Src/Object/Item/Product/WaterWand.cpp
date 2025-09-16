#include "WaterWand.h"

#include "../../../Manager/Generic/ResourceManager.h"

WaterWand::WaterWand(void)
	:ProductItem
	(
		"WaterWand",
		"ウォーターワンド",
		"水属性を宿した杖\n 材料\n ・水の魔石×２\n ・杖×１",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WATER_WAND).handleId_,
		0
	)
{
}
