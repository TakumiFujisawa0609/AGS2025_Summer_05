#include "gardenStage.h"

#include<DxLib.h>

#include"../Application.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Object/Manager/StageManager.h"

//コンストラクタ
GardenStage::GardenStage(void)
{
}

//初期化処理
void GardenStage::Init(void)
{
}

//更新処理
void GardenStage::Update(void)
{
	auto& input = InputManager::GetInstance();

	//ステージ遷移(デバッグ)
	if (input.IsTrgDown(KEY_INPUT_P))
	{
		//ステージ遷移
		StageManager::GetInstance().ChangeStage(StageManager::STAGE_ID::GUILD);
	}
}

//描画処理
void GardenStage::Draw(void)
{
	DrawFormatString(0, 20, 0xffffff, "ガーデン");
}

//解放処理
void GardenStage::Release(void)
{
}
