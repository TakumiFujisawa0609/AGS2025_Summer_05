#include "DarkWand.h"

#include "../../../Manager/Generic/ResourceManager.h"

DarkWand::DarkWand(void)
	:ProductItem
	(
		"DarkWand",
		"ƒ_[ƒNƒƒ“ƒh",
		"ˆÅ‘®«‚ğh‚µ‚½ñ\n Ş—¿\n EˆÅ‚Ì–‚Î~‚Q\n Eñ~‚P",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::DARK_WAND).handleId_,
		0
	)
{
}
