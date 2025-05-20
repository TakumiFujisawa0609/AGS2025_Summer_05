#include "Herb.h"

#include<DxLib.h>

//薬草の名前・説明・初期所持数を指定して基底クラスのコンストラクタを呼び出す
Herb::Herb(void) : ItemBase(name_, description_, quantity_, imageHandle_)
{
	name_ = "薬草";
	description_ = "HPを回復する薬草";
	quantity_ = 0;
	LoadGraph("");
};