#include "WindMagicStone.h"

#include "../../../Manager/Generic/ResourceManager.h"

WindMagicStone::WindMagicStone(void)
	:MaterialItem
	(
		"WindMagicStone",
		"•—‚Ì–‚Î",
		"•—‘®«‚ğh‚µ‚½–‚Î\n•Ší‚ğì‚éÛ‚É•—‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WIND_MAGIC_STONE).handleId_,
		0
	)
{
}
