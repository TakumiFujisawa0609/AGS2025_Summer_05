#pragma once
#include "DxLib.h"
#include<memory>

#include"StageBase.h"

class AtelierStage : public StageBase
{
public:

	//	鍋の大きさ
	static constexpr VECTOR STAGE_SCALEA = { 5.0f,5.0f,5.0f };

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

	//	工房のサンプル図
	int workshop_;

	//	鍋
	int modelId_;

	//　薬
	int kusuri_;

	int NowInput, EdgeInput, PrevInput;
	int Catch;
	int CatchMouseX, CatchMouseY;

	VECTOR Catch3DModelPosition;
	VECTOR Catch3DHitPosition;
	VECTOR Catch2DHitPosition;
};

