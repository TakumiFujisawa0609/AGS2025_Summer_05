#include "AntidotePotion.h"

#include "../../../Manager/Generic/ResourceManager.h"

AntidotePotion::AntidotePotion(void)
	:ProductItem
	(
		"AntidotePotion",
		"‰ğ“Åƒ|[ƒ\ƒ“",
		"ˆù‚Ş‚Æ“Å‚ÌŒø—Í‚ğ’†˜a‚·‚é\n Ş—¿\n E‰ğ“Å‘~‚Q\n E…~‚P",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ANTIDOTE_POTION).handleId_,
		0
	)
{
}
