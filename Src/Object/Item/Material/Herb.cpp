#include "Herb.h"

#include "../../../Manager/Generic/ResourceManager.h"

// 薬草の名前・説明・初期所持数・画像ハンドルを指定して基底クラスのコンストラクタを呼び出す
Herb::Herb(void)
	: MaterialItem
	(
		"Herb",
		"薬草", 
		"潰してエキスなどを負傷箇所にかけると治りが少し早くなる",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::HERB).handleId_
	)
{
}
