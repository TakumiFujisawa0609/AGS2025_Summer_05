#include "AtelierStage.h"

#include<DxLib.h>

#include"../Application.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Object/Manager/StageManager.h"


//コンストラクタ
AtelierStage::AtelierStage(void)
{

}

//初期化処理
void AtelierStage::Init(void)
{

}

//更新処理
void AtelierStage::Update(void)
{
	auto& input = InputManager::GetInstance();

	//ステージ遷移(デバッグ)
	if (input.IsTrgDown(KEY_INPUT_P))
	{
		//ステージ遷移
		StageManager::GetInstance().ChangeStage(StageManager::STAGE_ID::GARDEN);
	}

}

//描画処理
void AtelierStage::Draw(void)
{
	DrawFormatString(0, 20, 0xffffff, "アトリエステージ");
}

//解放処理
void AtelierStage::Release(void)
{

}