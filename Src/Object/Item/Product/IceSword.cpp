#include "IceSword.h"

#include "../../../Manager/Generic/ResourceManager.h"

IceSword::IceSword(void)
	:ProductItem
	(
		"IceSword",
		"ƒAƒCƒXƒ\[ƒh",
		"•X‘®«‚ğh‚µ‚½Œ•\n Ş—¿\n E•X‚Ì–‚Î~‚Q\n EŒ•~‚P",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ICE_SWORD).handleId_,
		0
	)
{
}
