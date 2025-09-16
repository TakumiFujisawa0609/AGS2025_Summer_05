#include "DarkMagicStone.h"

#include "../../../Manager/Generic/ResourceManager.h"

DarkMagicStone::DarkMagicStone(void)
	:MaterialItem
	(
		"DarkMagicStone",
		"ˆÅ‚Ì–‚Î",
		"ˆÅ‘®«‚ğh‚µ‚½–‚Î\n•Ší‚ğì‚éÛ‚ÉˆÅ‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::DARK_MAGIC_STONE).handleId_,
		0
	)
{
}
