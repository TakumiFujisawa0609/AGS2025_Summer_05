#include "Garbage.h"

#include "../../../Manager/Generic/ResourceManager.h"

Garbage::Garbage(void)
	:ProductItem
	(
		"Garbage",
		"¸”s‚Ìì•i",
		"‰½‚É‚àg‚¦‚È‚¢‚à‚Ì",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::GARBAGE).handleId_,
		0
	)
{
}
