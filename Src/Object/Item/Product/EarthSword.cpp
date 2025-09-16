#include "EarthSword.h"

#include "../../../Manager/Generic/ResourceManager.h"

EarthSword::EarthSword(void)
	:ProductItem
	(
		"EarthSword",
		"ƒA[ƒXƒ\[ƒh",
		"“y‘®«‚ğh‚µ‚½Œ•\n Ş—¿\n E“y‚Ì–‚Î~‚Q\n Œ•~‚P",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::EARTH_SWORD).handleId_,
		0
	)
{
}
