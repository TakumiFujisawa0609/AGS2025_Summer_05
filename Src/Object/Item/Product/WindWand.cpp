#include "WindWand.h"

#include "../../../Manager/Generic/ResourceManager.h"

WindWand::WindWand(void)
	:ProductItem
	(
		"WindWand",
		"ƒEƒBƒ“ƒhƒƒ“ƒh",
		"•—‘®«‚ğh‚µ‚½ñ\n Ş—¿\n E•—‚Ì–‚Î~‚Q\n Eñ~‚P",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WIND_WAND).handleId_,
		0
	)
{
}
