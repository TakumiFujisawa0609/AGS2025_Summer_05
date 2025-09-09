#include "Speed​​Potion.h"

#include "../../../Manager/Generic/ResourceManager.h"

Speed​​Potion::Speed​​Potion(void)
	:ProductItem
	(
		"SpeedPotion",
		"俊敏ポーソン",
		"飲むと一時的に動きが早くなる効果がある\n 材料\n ・風走草×２\n ・水×1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SPEED_POTION).handleId_,
		0
	)
{
}
