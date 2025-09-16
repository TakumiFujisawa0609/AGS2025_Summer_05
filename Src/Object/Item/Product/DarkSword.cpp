#include "DarkSword.h"

#include "../../../Manager/Generic/ResourceManager.h"

DarkSword::DarkSword(void)
	:ProductItem
	(
		"DarkSword",
		"ダークソード",
		"闇属性を宿した剣\n 材料\n ・闇の魔石×２\n ・剣×１",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::DARK_SWORD).handleId_,
		0
	)
{
}
