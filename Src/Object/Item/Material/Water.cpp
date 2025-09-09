#include "Water.h"

#include "../../../Manager/Generic/ResourceManager.h"

// 薬草の名前・説明・初期所持数・画像ハンドルを指定して基底クラスのコンストラクタを呼び出す
Water::Water(void)
	: MaterialItem
	(
		"Water",
		"水",
		"新鮮な水、用とはいろいろあるよ",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WATER).handleId_,
		0
	)
{
}
