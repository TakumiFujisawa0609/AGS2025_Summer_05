#include "FireWand.h"

#include "../../../Manager/Generic/ResourceManager.h"

FireWand::FireWand(void)
	:ProductItem
	(
		"FireWand",
		"ƒtƒŒƒCƒ€ƒƒ“ƒh",
		"‰Î‘®«‚ğh‚µ‚½ñ\n Ş—¿\n E‰Î‚Ì–‚Î~‚Q\n Eñ~‚P",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FIRE_WAND).handleId_,
		0
	)
{
}
