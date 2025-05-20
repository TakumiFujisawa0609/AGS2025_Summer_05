#include "AntidoteHerb.h"

#include<DxLib.h>

//薬草の名前・説明・初期所持数を指定して基底クラスのコンストラクタを呼び出す
AntidoteHerb::AntidoteHerb(void) : ItemBase(name_, description_, quantity_, imageHandle_)
{
	name_ = "毒消し草";
	description_ = "強烈な苦みがあるが解毒の効能がある";
	quantity_ = 0;
	LoadGraph("");
}