#pragma once

#include<memory>

#include"StageBase.h"

class AtelierStage : public StageBase
{
public:
	// 鍋のサイズ
	static constexpr VECTOR MODEILD_ = { 0.5f, 0.5f, 0.5f };

	// 薬のサイズ
	static constexpr int KUSURI_X = 60;
	static constexpr int KUSURI_Y = 60;

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
	int modelId_X;
	int modelId_Y;

	//　薬
	int kusuri_;
	int kusuri_X;
	int kusuri_Y;

	// マウス座標
	int mouseInput;
	int mouseX;
	int mouseY;
	int offsetX;
	int offsetY;

	bool isModelId_;
};

