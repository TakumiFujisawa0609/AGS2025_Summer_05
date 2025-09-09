#include "FireSword.h"

#include "../../../Manager/Generic/ResourceManager.h"

FireSword::FireSword(void)
	:ProductItem
	(
		"FireSword",
		"‰Î‚ÌŒ•",
		"‰Î‘®«‚ğh‚µ‚½Œ•\n Ş—¿\n E‰Î‚Ì–‚Î~‚Q\n EŒ•~1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FIRE_SORD).handleId_,
		0
	)
{
}
