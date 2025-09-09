#include "DemonPowerHerb.h"

#include "../../../Manager/Generic/ResourceManager.h"

DemonPowerHerb::DemonPowerHerb(void)
	:MaterialItem
	(
		"DemonPowerHerb",
		"鬼力草",
		"鬼と似たような力を得る薬草\n潰したエキスを摂取すると一時的に力を高める効果がある\n他の薬草をと混ぜるな危険",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::DEMON_POWER_HERB).handleId_,
		0
	)
{
}
