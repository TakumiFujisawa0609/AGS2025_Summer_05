#include "LightMagicStone.h"

#include "../../../Manager/Generic/ResourceManager.h"

LightMagicStone::LightMagicStone(void)
	:MaterialItem
	(
		"LightMagicStone",
		"Œõ‚Ì–‚Î",
		"Œõ‘®«‚ğh‚µ‚½–‚Î\n•Ší‚ğì‚éÛ‚ÉŒõ‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::LIGHT_MAGIC_STONE).handleId_,
		0
	)
{
}
