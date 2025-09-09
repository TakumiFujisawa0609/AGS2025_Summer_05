#include "DefensePotion.h"

#include "../../../Manager/Generic/ResourceManager.h"

DefensePotion::DefensePotion(void)
	:ProductItem
	(
		"DefensePotion",
		"–hŒäƒ|[ƒ\ƒ“",
		"ˆù‚Ş‚Æˆê“I‚É–hŒä—Í‚ª‚‚Ü‚éŒø‰Ê‚ª‚ ‚é\n Ş—¿\n E–ƒáƒ‘~‚Q\n E…~1",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::DEFENSE_POTION).handleId_,
		0
	)
{
}
