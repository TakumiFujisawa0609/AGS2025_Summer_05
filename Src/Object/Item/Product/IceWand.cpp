#include "IceWand.h"

#include "../../../Manager/Generic/ResourceManager.h"

IceWand::IceWand(void)
	:ProductItem
	(
		"IceWand",
		"ƒAƒCƒXƒƒ“ƒh",
		"•X‘®«‚ğh‚µ‚½ñ\n Ş—¿\n E•X‚Ì–‚Î~‚Q\n Eñ~‚P",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ICE_WAND).handleId_,
		0
	)
{
}
