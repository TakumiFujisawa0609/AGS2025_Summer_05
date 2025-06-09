#include<DxLib.h>
#include "AtelierStage.h"
#include"../Application.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Object/Manager/StageManager.h"
#include "../Object/AtelierObject/AlchemyPot.h"
#include "../Object/Manager/CollisionManager.h"


//コンストラクタ
AtelierStage::AtelierStage(void)
{

}

//初期化処理
void AtelierStage::Init(void)
{

	//	鍋
	modelId_= MV1LoadModel("Data/Model/Stage/Grand.mv1");
	
	////	薬
	//kusuri_ = MV1LoadModel("Data/Model/Iitem/Iitem.mv1");

	////	薬
	//kusuri2_ = MV1LoadModel("Data/Model/Iitem/Iitem2.mv1");

	// 変数の初期化
	NowInput = 0;
	EdgeInput = 0;
	PrevInput = 0;
	Catch = 0;

	// 変数の初期化
	NowInput2 = 0;
	EdgeInput2 = 0;
	PrevInput2 = 0;
	Catch2 = 0;


	// 鍋-------------------------------------------------------------------------
	// 鍋の位置
	modelIdPos_ = INIT_MODELID_POS;
	// 座標をモデルに設定
	MV1SetPosition(modelId_, modelIdPos_);
	// 鍋の大きさ
	MV1SetScale(modelId_, MODELID_SCALEA);
	// 生存判定
	isModelId_ = true;



	// 薬-------------------------------------------------------------------------

	//// 薬の位置
	//kusuriPos_ = INIT_KUSURI_POS;
	//// 薬座標をモデルに設定
	//MV1SetPosition(kusuri_, kusuriPos_);
	//// 生存判定
	//isKusuri_ = true;

	//// 薬の位置
	//kusuriPos2_ = INIT_KUSURI_POS2;
	//// 薬座標をモデルに設定
	//MV1SetPosition(kusuri2_, kusuriPos2_);
	//// 生存判定
	//isKusuri2_ = true;

	alchemyPot_ = std::make_shared<AlchemyPot>();
	alchemyPot_->Init();
	CollisionManager::GetInstance().Register(alchemyPot_);

	teleportt_ = std::make_shared<Teleport>();
	teleportt_->Init();
	CollisionManager::GetInstance().Register(teleportt_);
	
}

void AtelierStage::Update(void)
{
	auto& input = InputManager::GetInstance();
	alchemyPot_->Update();
	teleportt_->Update();

	// ステージ遷移(デバッグ)
	if (input.IsTrgDown(KEY_INPUT_P))
	{
		//ステージ遷移
		StageManager::GetInstance().ChangeStage(StageManager::STAGE_ID::GARDEN);
	}
		
}

////更新処理
//void AtelierStage::Update(void)
//{
//
//	auto& input = InputManager::GetInstance();
//	
//	//ステージ遷移(デバッグ)
//	if (input.IsTrgDown(KEY_INPUT_P))
//	{
//		//ステージ遷移
//		StageManager::GetInstance().ChangeStage(StageManager::STAGE_ID::GARDEN);
//	}
//
//
//	// ウインドウモードで起動
//	ChangeWindowMode(TRUE);
//	
//	int MouseX, MouseY;
//
//	// マウスカーソルの座標を取得
//	GetMousePoint(&MouseX, &MouseY);
//
//	// マウスボタンの入力状態を更新
//	PrevInput = NowInput;
//	NowInput = GetMouseInput();
//	EdgeInput = NowInput & ~PrevInput;
//
//	// 既にモデルを掴んでいるかどうかで処理を分岐
//	if (Catch == 0)
//	{
//		// 掴んでいない場合
//
//		// 左クリックされたらモデルをクリックしたかを調べる
//		if (EdgeInput & MOUSE_INPUT_1)
//		{
//			VECTOR ScreenPos1;
//			VECTOR ScreenPos2;
//			VECTOR WorldPos1;
//			VECTOR WorldPos2;
//
//			// モデルとの当たり判定用の線分の２座標を作成
//			ScreenPos1.x = (float)MouseX;
//			ScreenPos1.y = (float)MouseY;
//			ScreenPos1.z = 0.0f;
//
//			ScreenPos2.x = (float)MouseX;
//			ScreenPos2.y = (float)MouseY;
//			ScreenPos2.z = 1.0f;
//
//			WorldPos1 = ConvScreenPosToWorldPos(ScreenPos1);
//			WorldPos2 = ConvScreenPosToWorldPos(ScreenPos2);
//
//			//// モデルの当たり判定情報を更新
//			//MV1RefreshCollInfo(kusuri_, -1);
//
//			//// モデルと線分の当たり判定
//			//MV1_COLL_RESULT_POLY Result = MV1CollCheck_Line(kusuri_, -1, WorldPos1, WorldPos2);
//
//			//// 当たっていたら掴み状態にする
//			//if (Result.HitFlag)
//			//{
//			//	// 掴んでいるかどうかのフラグを立てる
//			//	Catch = 1;
//
//			//	// 掴んだときのスクリーン座標を保存
//			//	CatchMouseX = MouseX;
//			//	CatchMouseY = MouseY;
//
//			//	//// 掴んだときのモデルのワールド座標を保存
//			//	//Catch3DModelPosition = MV1GetPosition(kusuri_);
//
//			//	// 掴んだときのモデルと線分が当たった座標を保存( 座標をスクリーン座標に変換したものも保存しておく )
//			//	Catch3DHitPosition = Result.HitPosition;
//			//	Catch2DHitPosition = ConvWorldPosToScreenPos(Catch3DHitPosition);
//			//}
//		}
//	}
//	else
//	{
//		// 掴んでいる場合
//
//		// マウスの左クリックが離されていたら掴み状態を解除
//		if ((NowInput & MOUSE_INPUT_1) == 0)
//		{
//			Catch = 0;
//		}
//		else
//		{
//			// 掴み状態が継続していたらマウスカーソルの移動に合わせてモデルも移動
//
//			float MoveX, MoveY;
//			VECTOR NowCatch2DHitPosition;
//			VECTOR NowCatch3DHitPosition;
//			VECTOR Now3DModelPosition;
//
//			// 掴んだときのマウス座標から現在のマウス座標までの移動分を算出
//			MoveX = (float)(MouseX - CatchMouseX);
//			MoveY = (float)(MouseY - CatchMouseY);
//
//			// 掴んだときのモデルと線分が当たった座標をスクリーン座標に変換したものにマウスの移動分を足す
//			NowCatch2DHitPosition.x = Catch2DHitPosition.x + MoveX;
//			NowCatch2DHitPosition.y = Catch2DHitPosition.y + MoveY;
//			NowCatch2DHitPosition.z = Catch2DHitPosition.z;
//
//			// 掴んだときのモデルと線分が当たった座標をスクリーン座標に変換したものにマウスの移動分を足した座標をワールド座標に変換
//			NowCatch3DHitPosition = ConvScreenPosToWorldPos(NowCatch2DHitPosition);
//
//			// 掴んだときのモデルのワールド座標に『掴んだときのモデルと線分が当たった座標にマウスの移動分を足した座標をワールド座標に
//			// 変換した座標』と、『掴んだときのモデルと線分が当たった座標』との差分を加算
//			Now3DModelPosition.x = 
//				Catch3DModelPosition.x 
//				+ NowCatch3DHitPosition.x 
//				- Catch3DHitPosition.x;
//
//			Now3DModelPosition.y = Catch3DModelPosition.y 
//				+ NowCatch3DHitPosition.y 
//				- Catch3DHitPosition.y;
//
//			Now3DModelPosition.z = Catch3DModelPosition.z
//				+ NowCatch3DHitPosition.z 
//				- Catch3DHitPosition.z;
//
//			//// ↑の計算で求まった新しい座標をモデルの座標としてセット
//			//MV1SetPosition(kusuri_, Now3DModelPosition);
//		}
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	// ウインドウモードで起動
//	ChangeWindowMode(TRUE);
//
//	int MouseX2, MouseY2;
//
//	// マウスカーソルの座標を取得
//	GetMousePoint(&MouseX2, &MouseY2);
//
//	// マウスボタンの入力状態を更新
//	PrevInput2 = NowInput2;
//	NowInput2 = GetMouseInput();
//	EdgeInput2 = NowInput2 & ~PrevInput2;
//
//	// 既にモデルを掴んでいるかどうかで処理を分岐
//	if (Catch2 == 0)
//	{
//		// 掴んでいない場合
//
//		// 左クリックされたらモデルをクリックしたかを調べる
//		if (EdgeInput2 & MOUSE_INPUT_1)
//		{
//			VECTOR ScreenPos1;
//			VECTOR ScreenPos2;
//			VECTOR WorldPos1;
//			VECTOR WorldPos2;
//
//			// モデルとの当たり判定用の線分の２座標を作成
//			ScreenPos1.x = (float)MouseX2;
//			ScreenPos1.y = (float)MouseY2;
//			ScreenPos1.z = 0.0f;
//
//			ScreenPos2.x = (float)MouseX2;
//			ScreenPos2.y = (float)MouseY2;
//			ScreenPos2.z = 1.0f;
//
//			WorldPos1 = ConvScreenPosToWorldPos(ScreenPos1);
//			WorldPos2 = ConvScreenPosToWorldPos(ScreenPos2);
//
//			//// モデルの当たり判定情報を更新
//			//MV1RefreshCollInfo(kusuri2_, -1);
//
//			//// モデルと線分の当たり判定
//			//MV1_COLL_RESULT_POLY Result = MV1CollCheck_Line(kusuri2_, -1, WorldPos1, WorldPos2);
//
//		//	// 当たっていたら掴み状態にする
//		//	if (Result.HitFlag)
//		//	{
//		//		// 掴んでいるかどうかのフラグを立てる
//		//		Catch2 = 1;
//
//		//		// 掴んだときのスクリーン座標を保存
//		//		CatchMouseX2 = MouseX2;
//		//		CatchMouseY2 = MouseY2;
//
//		//		// 掴んだときのモデルのワールド座標を保存
//		//		Catch3DModelPosition2 = MV1GetPosition(kusuri2_);
//
//		//		// 掴んだときのモデルと線分が当たった座標を保存( 座標をスクリーン座標に変換したものも保存しておく )
//		//		Catch3DHitPosition2 = Result.HitPosition;
//		//		Catch2DHitPosition2 = ConvWorldPosToScreenPos(Catch3DHitPosition2);
//		//	}
//		//}
//	}
//	else
//	{
//		// 掴んでいる場合
//
//		// マウスの左クリックが離されていたら掴み状態を解除
//		if ((NowInput2 & MOUSE_INPUT_1) == 0)
//		{
//			Catch2 = 0;
//		}
//		else
//		{
//			// 掴み状態が継続していたらマウスカーソルの移動に合わせてモデルも移動
//
//			float MoveX, MoveY;
//			VECTOR NowCatch2DHitPosition;
//			VECTOR NowCatch3DHitPosition;
//			VECTOR Now3DModelPosition;
//
//			// 掴んだときのマウス座標から現在のマウス座標までの移動分を算出
//			MoveX = (float)(MouseX2 - CatchMouseX2);
//			MoveY = (float)(MouseY2 - CatchMouseY2);
//
//			// 掴んだときのモデルと線分が当たった座標をスクリーン座標に変換したものにマウスの移動分を足す
//			NowCatch2DHitPosition.x = Catch2DHitPosition2.x + MoveX;
//			NowCatch2DHitPosition.y = Catch2DHitPosition2.y + MoveY;
//			NowCatch2DHitPosition.z = Catch2DHitPosition2.z;
//
//			// 掴んだときのモデルと線分が当たった座標をスクリーン座標に変換したものにマウスの移動分を足した座標をワールド座標に変換
//			NowCatch3DHitPosition = ConvScreenPosToWorldPos(NowCatch2DHitPosition);
//
//			// 掴んだときのモデルのワールド座標に『掴んだときのモデルと線分が当たった座標にマウスの移動分を足した座標をワールド座標に
//			// 変換した座標』と、『掴んだときのモデルと線分が当たった座標』との差分を加算
//			Now3DModelPosition.x =
//				Catch3DModelPosition2.x
//				+ NowCatch3DHitPosition.x
//				- Catch3DHitPosition2.x;
//
//			Now3DModelPosition.y = Catch3DModelPosition2.y
//				+ NowCatch3DHitPosition.y
//				- Catch3DHitPosition2.y;
//
//			Now3DModelPosition.z = Catch3DModelPosition2.z
//				+ NowCatch3DHitPosition.z
//				- Catch3DHitPosition2.z;
//
//			//// ↑の計算で求まった新しい座標をモデルの座標としてセット
//			//MV1SetPosition(kusuri2_, Now3DModelPosition);
//		}
//	}
//}

//描画処理
void AtelierStage::Draw(void)
{
	DrawFormatString(0, 20, 0xffffff, "アトリエステージ");

	

	// 鍋の描画
	if (isModelId_)
	{
		MV1DrawModel(modelId_);
	}

	alchemyPot_->Draw();
	teleportt_->Draw();


	//// 薬の描画
	//if (isKusuri_)
	//{
	//	MV1DrawModel(kusuri_);
	//}

	//// 薬の描画
	//if (isKusuri2_)
	//{
	//	MV1DrawModel(kusuri2_);
	//}
}

//解放処理
void AtelierStage::Release(void)
{
	// メモリから解放する
	MV1DeleteModel(modelId_);

	/*MV1DeleteModel(kusuri_);

	MV1DeleteModel(kusuri2_);*/

}