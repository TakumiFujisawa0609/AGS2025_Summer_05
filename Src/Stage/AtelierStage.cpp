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
	//	工房のサンプル図
	workshop_ = LoadGraph("Data/Model/Atelier/Magic Workshop.png");

	//	鍋
	modelId_= MV1LoadModel("Data/Model/Atelier/Grand.mv1");
	
	
	//	薬
	kusuri_ = LoadGraph("Data/Model/Atelier/Kusuri.png");


	offsetX = 0;
	offsetY = 0;

	isModelId_ = false;

	modelId_X = 100;
	modelId_Y = 100;
	GetGraphSize(modelId_, &modelId_X, &modelId_Y);

	kusuri_X = 50;
	kusuri_Y = 50;
	GetGraphSize(kusuri_, &kusuri_X, &kusuri_Y);
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

	

	// マウスの位置とキーの状態を取得する
	// 获取鼠标位置和按键状态
	mouseInput = GetMouseInput();

	GetMousePoint(&mouseX, &mouseY);

	//// マウスのボタンの押下状態を取得する
	//if (mouseInput & MOUSE_INPUT_LEFT) 
	//{ 
	//	// マウスの左ボタンが押されました
	//	// 鼠标左键按下
	//	if (!isModelId_)
	//	{
	//		// ドラッグ開始判定
	//		if (mouseX >= modelId_X
	//			&& mouseX <= modelId_X + MODEILD_X
	//			&& mouseY >= modelId_Y
	//			&& mouseY <= modelId_Y + MODEILD_Y)
	//		{
	//			isModelId_ = true;
	//			offsetX = mouseX - modelId_X;
	//			offsetY = mouseY - modelId_Y;
	//		}
	//	}
	//	else {
	//		// ドラッグ中の位置更新
	//		modelId_X = mouseX - offsetX;
	//		modelId_Y = mouseY - offsetY;

	//		// 範囲制限（ウィンドウ内に収める）
	//		if (modelId_X < 0) modelId_X = 0;
	//		if (modelId_Y < 0) modelId_Y = 0;
	//		if (modelId_X + MODEILD_X > 640) modelId_X = 640 - MODEILD_X;
	//		if (modelId_Y + MODEILD_Y > 480) modelId_Y = 480 - MODEILD_Y;
	//	}
	//}
	//else 
	//{
	//	// マウスを離すと、ドラッグを停止します。
	//	// 鼠标释放，停止拖动
	//	isModelId_ = false;
	//}


	// 薬
	// マウスのボタンの押下状態を取得する
	if (mouseInput & MOUSE_INPUT_LEFT)
	{
		// マウスの左ボタンが押されました
		// 鼠标左键按下
		if (!isModelId_)
		{
			// ドラッグ開始判定
			if (mouseX >= kusuri_X
				&& mouseX <= kusuri_X + KUSURI_X
				&& mouseY >= kusuri_Y
				&& mouseY <= kusuri_Y + KUSURI_Y)
			{
				isModelId_ = true;
				offsetX = mouseX - kusuri_X;
				offsetY = mouseY - kusuri_Y;
			}
		}
		else {
			// ドラッグ中の位置更新
			kusuri_X = mouseX - offsetX;
			kusuri_Y = mouseY - offsetY;

			// 範囲制限（ウィンドウ内に収める）
			if (kusuri_X < 0) kusuri_X = 0;
			if (kusuri_Y < 0) kusuri_Y = 0;
			if (kusuri_X + KUSURI_X > Application::DEFA_SCREEN_SIZE_X)
				kusuri_X = Application::DEFA_SCREEN_SIZE_X - KUSURI_X;
			if (kusuri_Y + KUSURI_Y > Application::DEFA_SCREEN_SZIE_Y)
				kusuri_Y = Application::DEFA_SCREEN_SZIE_Y - KUSURI_Y;
		}
	}
	else
	{
		// マウスを離すと、ドラッグを停止します。
		// 鼠标释放，停止拖动
		isModelId_ = false;
	}
}

//描画処理
void AtelierStage::Draw(void)
{
	DrawFormatString(0, 20, 0xffffff, "アトリエステージ");

	DrawGraph(0, 0, workshop_, true);

	DrawGraph(modelId_X, modelId_Y, modelId_, true);
	DrawFormatString(0, 0,
		0x000000, "modelId_座標：{ %d, %d }",
		modelId_X, modelId_Y);

	DrawGraph(kusuri_X, kusuri_Y, kusuri_, true);
	DrawFormatString(0, 20,
		0x000000, "kusuri_座標：{ %d, %d }",
		kusuri_X, kusuri_Y);
}

//解放処理
void AtelierStage::Release(void)
{

}