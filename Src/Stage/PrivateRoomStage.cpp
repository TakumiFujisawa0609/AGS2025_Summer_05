#include "PrivateRoomStage.h"

#include<DxLib.h>

#include"../Application.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Object/Manager/StageManager.h"

//コンストラクタ
PrivateRoomStage::PrivateRoomStage(void)
{
}

//初期化処理
void PrivateRoomStage::Init(void)
{
}

//更新処理
void PrivateRoomStage::Update(void)
{
	auto& input = InputManager::GetInstance();
}

//描画処理
void PrivateRoomStage::Draw(void)
{
	DrawFormatString(0, 20, 0xffffff, "プライベート");
}

//解放処理
void PrivateRoomStage::Release(void)
{
}
