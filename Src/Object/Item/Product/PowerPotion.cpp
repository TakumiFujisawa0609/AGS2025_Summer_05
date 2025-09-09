#include "PowerPotion.h"

#include "../../../Manager/Generic/ResourceManager.h"

PowerPotion::PowerPotion(void)
	:ProductItem
	(
		"PowerPotion",
		"力のポーソン",
		"飲むと一時的に力が高まる効果がある\n 材料\n ・鬼力草×２\n ・水×1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::POWER_POTION).handleId_,
		0
	)
{
}
