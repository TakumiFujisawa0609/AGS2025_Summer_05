#include "WaterSword.h"

#include "../../../Manager/Generic/ResourceManager.h"

WaterSword::WaterSword(void)
	:ProductItem
	(
		"WaterSword",
		"…‚ÌŒ•",
		"…‘®«‚ğh‚µ‚½Œ•\n Ş—¿\n E…‚Ì–‚Î~‚Q\n EŒ•~1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WATER_SWORD).handleId_,
		0
	)
{
}
