#include "EarthMagicStone.h"

#include "../../../Manager/Generic/ResourceManager.h"

EarthMagicStone::EarthMagicStone(void)
	:MaterialItem
	(
		"EarthMagicStone",
		"“y‚Ì–‚Î",
		"“y‘®«‚ğh‚µ‚½–‚Î\n•Ší‚ğì‚éÛ‚É“y‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::EARTH_MAGIC_STONE).handleId_,
		0
	)
{
}
