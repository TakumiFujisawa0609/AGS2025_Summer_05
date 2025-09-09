#include "HardbodyHerb.h"

#include "../../../Manager/Generic/ResourceManager.h"

HardbodyHerb::HardbodyHerb(void)
	:MaterialItem
	(
		"HardbodyHerb",
		"硬体草",
		"体を硬くする効果がある薬草\n潰したエキスを水で薄めて摂取すると一時的に身体が硬くなる効果がある\n他の薬草をと混ぜるな危険",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::HARD_BODY_HERB).handleId_,
		0
	)
{
}
