#include "Emberstone.h"
#include "../../../Manager/Generic/ResourceManager.h"
Emberstone::Emberstone(void)
	: MaterialItem
	(
		"EmberStone",
		"エンバーストーン",
		"火の力が長い年月をかけて凝縮されたい石",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::EMBER_STONE).handleId_
	)
{
}
