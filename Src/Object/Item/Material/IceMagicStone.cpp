#include "IceMagicStone.h"

#include "../../../Manager/Generic/ResourceManager.h"

IceMagicStone::IceMagicStone(void)
	:MaterialItem
	(
		"IceMagicStone",
		"•X‚Ì–‚Î",
		"•X‘®«‚ğh‚·–‚Î^\n•Ší‚ğì‚éÛ‚É•X‘®«‚ğ—^‚¦‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ICE_MAGIC_STONE).handleId_,
		0
	)
{
}
