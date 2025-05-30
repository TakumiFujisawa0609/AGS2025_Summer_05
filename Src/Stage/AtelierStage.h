#pragma once
#include "DxLib.h"
#include<memory>

#include"StageBase.h"

class AtelierStage : public StageBase
{
public:

	//	鍋の大きさ
	static constexpr VECTOR MODELID_SCALEA = { 5.0f,5.0f,5.0f };

	// 鍋の初期位置
	static constexpr VECTOR INIT_MODELID_POS = { 100.0f, 60.0f, 0.0f };

	//  鍋の衝突判定用半径
	static constexpr float RADIUS_MODELID = 120.0f;



	// 薬の初期位置
	static constexpr VECTOR INIT_KUSURI_POS = { 100.0f, 70.0f, 0.0f };

	// 薬の衝突判定用半径
	static constexpr float RADIUS_KUSURI = 80.0f;

	//コンストラクタ
	AtelierStage(void);

	//デストラクタ
	~AtelierStage(void) = default;

	//初期化処理
	void Init(void) override;

	//更新処理
	void Update(void) override;

	//描画処理
	void Draw(void) override;

	//解放処理
	void Release(void) override;

private:

	// 球体位置
	VECTOR spherePos = { 0.0f, 20.0f, 0.0f };

	//	工房のサンプル図
	int workshop_;

	//	鍋
	int modelId_;
	VECTOR modelIdPos_;
	// 鍋の生存判定
	bool isModelId_;

	//　薬
	int kusuri_;
	VECTOR kusuriPos_;
	// 薬の生存判定
	bool isKusuri_;

	// マウスボタンの状態
	int NowInput, EdgeInput, PrevInput;
	int Catch;
	int CatchMouseX, CatchMouseY;

	VECTOR Catch3DModelPosition;
	VECTOR Catch3DHitPosition;
	VECTOR Catch2DHitPosition;
};

