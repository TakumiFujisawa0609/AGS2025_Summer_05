#include "EarthWand.h"

#include "../../../Manager/Generic/ResourceManager.h"

EarthWand::EarthWand(void)
	:ProductItem
	(
		"EarthWand",
		"ƒA[ƒXƒƒ“ƒh",
		"“y‘®«‚ğh‚µ‚½ñ\n Ş—¿\n E“y‚Ì–‚Î~‚Q\n Eñ~‚P",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::EARTH_WAND).handleId_,
		0
	)
{
}
