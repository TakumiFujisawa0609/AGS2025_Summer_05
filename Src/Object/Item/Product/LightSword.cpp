#include "LightSword.h"

#include "../../../Manager/Generic/ResourceManager.h"

LightSword::LightSword(void)
	:ProductItem
	(
		"LightSword",
		"ライトソード",
		"光属性を宿した剣\n 材料\n ・光の魔石×２\n ・剣×１",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::LIGHT_SWORD).handleId_,
		0
	)
{
}
