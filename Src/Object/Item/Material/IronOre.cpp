#include "IronOre.h"

#include "../../../Manager/Generic/ResourceManager.h"

IronOre::IronOre(void)
	:MaterialItem
	(
		"IronOre",
		"“SzÎ",
		"“S‚ÌzÎ\nŒ•‚ÌŒ´Œ^‚âAñ‚ÌŒ´Œ^‚ğì‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::IRON_ORE).handleId_,
		0
	)
{
}
