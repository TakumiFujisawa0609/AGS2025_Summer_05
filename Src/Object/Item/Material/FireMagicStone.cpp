#include "FireMagicStone.h"

#include "../../../Manager/Generic/ResourceManager.h"

FireMagicStone::FireMagicStone(void)
	:MaterialItem
	(
		"FireMagicStone",
		"‰Î‚Ì–‚Î",
		"‰Î‘®«‚ğh‚·–‚Î\n•Ší‚ğì‚éÛ‚É‰Î‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FIRE_MAGIC_STONE).handleId_,
		0
	)
{
}
