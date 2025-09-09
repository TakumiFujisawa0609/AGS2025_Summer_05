#include "Herb.h"

#include "../../../Manager/Generic/ResourceManager.h"

// 薬草の名前・説明・初期所持数・画像ハンドルを指定して基底クラスのコンストラクタを呼び出す
Herb::Herb(void)
	: MaterialItem
	(
		"Herb",
		"薬草", 
		"体を癒す効果がある\n潰してエキスなどを負傷箇所にかけると治りが少し早くなる\n他の薬草をと混ぜるな危険",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::HERB).handleId_,
		1000
	)
{
}
