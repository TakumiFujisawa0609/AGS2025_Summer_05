#include "RandomSeed.h"

#include "../../../Manager/Generic/ResourceManager.h"

//コンストラクタ
RandomSeed::RandomSeed(void)
	:SeedItem
	(
		"RandomSeed",
		"種子",
		"特殊な種子なにが取れるかは運しだい",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SEED).handleId_,
		100
	)
{
}