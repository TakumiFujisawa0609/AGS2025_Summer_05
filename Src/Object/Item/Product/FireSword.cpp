#include "FireSword.h"

#include "../../../Manager/Generic/ResourceManager.h"

FireSword::FireSword(void)
	:ProductItem
	(
		"FireSword",
		"フレイムソード",
		"火属性を宿した剣\n 材料\n ・火の魔石×２\n ・剣×1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FIRE_SORD).handleId_,
		0
	)
{
}
