#include "GaleHerb.h"

#include "../../../Manager/Generic/ResourceManager.h"

GaleHerb::GaleHerb(void)
	:MaterialItem
	(
		"GaleHerb",
		"風走草",
		"風の力を宿す不思議な草\n潰したエキスを摂取すると一時的に身体が軽くなる効果がある\n他の薬草をと混ぜるな危険",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::GALE_HERB).handleId_,
		0
	)
{
}