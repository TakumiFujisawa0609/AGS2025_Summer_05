#include "LightWand.h"

#include "../../../Manager/Generic/ResourceManager.h"

LightWand::LightWand(void)
	:ProductItem
	(
		"LightWand",
		"ƒ‰ƒCƒgƒƒ“ƒh",
		"Œõ‘®«‚ğh‚µ‚½ñ\n Ş—¿\n EŒõ‚Ì–‚Î~‚Q\n Eñ~‚P",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::LIGHT_WAND).handleId_,
		0
	)
{
}
