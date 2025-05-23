#include "MagicPotion.h"

#include "../../../Manager/Generic/Resource.h"
#include "../../../Manager/Generic/ResourceManager.h"

MagicPotion::MagicPotion(void)
	:ProductItem
	(
		"–‚—Íƒ|[ƒ\ƒ“",
		"ˆù‚Ş‚Æ–‚—Í‚ğ‰ñ•œ‚·‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::MAGIC_POTION).handleId_
	)
{
}
