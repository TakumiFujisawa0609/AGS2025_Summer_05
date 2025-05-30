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
	modelId_= MV1LoadModel("Data/Model/Stage/Grand.mv1");
	
	//	薬
	kusuri_ = MV1LoadModel("Data/Model/Iitem/Iitem.mv1");

	// 変数の初期化
	NowInput = 0;
	EdgeInput = 0;
	PrevInput = 0;
	Catch = 0;

	MV1SetScale(modelId_, STAGE_SCALEA);

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


	// ウインドウモードで起動
	ChangeWindowMode(TRUE);


	int MouseX, MouseY;

	// マウスカーソルの座標を取得
	GetMousePoint(&MouseX, &MouseY);

	// マウスボタンの入力状態を更新
	PrevInput = NowInput;
	NowInput = GetMouseInput();
	EdgeInput = NowInput & ~PrevInput;

	// 既にモデルを掴んでいるかどうかで処理を分岐
	if (Catch == 0)
	{
		// 掴んでいない場合

		// 左クリックされたらモデルをクリックしたかを調べる
		if (EdgeInput & MOUSE_INPUT_1)
		{
			VECTOR ScreenPos1;
			VECTOR ScreenPos2;
			VECTOR WorldPos1;
			VECTOR WorldPos2;

			// モデルとの当たり判定用の線分の２座標を作成
			ScreenPos1.x = (float)MouseX;
			ScreenPos1.y = (float)MouseY;
			ScreenPos1.z = 0.0f;

			ScreenPos2.x = (float)MouseX;
			ScreenPos2.y = (float)MouseY;
			ScreenPos2.z = 1.0f;

			WorldPos1 = ConvScreenPosToWorldPos(ScreenPos1);
			WorldPos2 = ConvScreenPosToWorldPos(ScreenPos2);

			// モデルの当たり判定情報を更新
			MV1RefreshCollInfo(modelId_, -1);

			// モデルと線分の当たり判定
			MV1_COLL_RESULT_POLY Result = MV1CollCheck_Line(modelId_, -1, WorldPos1, WorldPos2);

			// 当たっていたら掴み状態にする
			if (Result.HitFlag)
			{
				// 掴んでいるかどうかのフラグを立てる
				Catch = 1;

				// 掴んだときのスクリーン座標を保存
				CatchMouseX = MouseX;
				CatchMouseY = MouseY;

				// 掴んだときのモデルのワールド座標を保存
				Catch3DModelPosition = MV1GetPosition(modelId_);

				// 掴んだときのモデルと線分が当たった座標を保存( 座標をスクリーン座標に変換したものも保存しておく )
				Catch3DHitPosition = Result.HitPosition;
				Catch2DHitPosition = ConvWorldPosToScreenPos(Catch3DHitPosition);
			}
		}
	}
	else
	{
		// 掴んでいる場合

		// マウスの左クリックが離されていたら掴み状態を解除
		if ((NowInput & MOUSE_INPUT_1) == 0)
		{
			Catch = 0;
		}
		else
		{
			// 掴み状態が継続していたらマウスカーソルの移動に合わせてモデルも移動

			float MoveX, MoveY;
			VECTOR NowCatch2DHitPosition;
			VECTOR NowCatch3DHitPosition;
			VECTOR Now3DModelPosition;

			// 掴んだときのマウス座標から現在のマウス座標までの移動分を算出
			MoveX = (float)(MouseX - CatchMouseX);
			MoveY = (float)(MouseY - CatchMouseY);

			// 掴んだときのモデルと線分が当たった座標をスクリーン座標に変換したものにマウスの移動分を足す
			NowCatch2DHitPosition.x = Catch2DHitPosition.x + MoveX;
			NowCatch2DHitPosition.y = Catch2DHitPosition.y + MoveY;
			NowCatch2DHitPosition.z = Catch2DHitPosition.z;

			// 掴んだときのモデルと線分が当たった座標をスクリーン座標に変換したものにマウスの移動分を足した座標をワールド座標に変換
			NowCatch3DHitPosition = ConvScreenPosToWorldPos(NowCatch2DHitPosition);

			// 掴んだときのモデルのワールド座標に『掴んだときのモデルと線分が当たった座標にマウスの移動分を足した座標をワールド座標に
			// 変換した座標』と、『掴んだときのモデルと線分が当たった座標』との差分を加算
			Now3DModelPosition.x = Catch3DModelPosition.x + NowCatch3DHitPosition.x - Catch3DHitPosition.x;
			Now3DModelPosition.y = Catch3DModelPosition.y + NowCatch3DHitPosition.y - Catch3DHitPosition.y;
			Now3DModelPosition.z = Catch3DModelPosition.z + NowCatch3DHitPosition.z - Catch3DHitPosition.z;

			// ↑の計算で求まった新しい座標をモデルの座標としてセット
			MV1SetPosition(modelId_, Now3DModelPosition);
		}
	}
}

//描画処理
void AtelierStage::Draw(void)
{
	DrawFormatString(0, 20, 0xffffff, "アトリエステージ");

	DrawGraph(0, 0, workshop_, true);

	// モデル描画
	MV1DrawModel(modelId_);

	MV1DrawModel(kusuri_);
}

//解放処理
void AtelierStage::Release(void)
{
	// メモリから解放する
	MV1DeleteModel(modelId_);

	MV1DeleteModel(kusuri_);

}