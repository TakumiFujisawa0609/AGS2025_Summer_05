#include "WaterMagicStone.h"

#include "../../../Manager/Generic/ResourceManager.h"

WaterMagicStone::WaterMagicStone(void)
	:MaterialItem
	(
		"WaterMagicStone",
		"…‚Ì–‚Î",
		"…‘®«‚ğh‚·–‚Î\n•Ší‚ğì‚éÛ‚É…‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WATER_MAGIC_STONE).handleId_,
		0
	)
{
}
