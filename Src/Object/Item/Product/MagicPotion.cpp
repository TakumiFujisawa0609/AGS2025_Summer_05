#include "MagicPotion.h"

#include "../../../Manager/Generic/ResourceManager.h"

MagicPotion::MagicPotion(void)
	:ProductItem
	(
		"MagicPotion",
		"魔力ポーソン",
		"飲むと魔力を回復する\n 材料\n ・魔力草×２\n ・水×1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::MAGIC_POTION).handleId_,
		0
	)
{
}
