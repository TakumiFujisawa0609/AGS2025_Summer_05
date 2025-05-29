#pragma once
#include<DxLib.h>

#include "UnitBase.h"

class Player : public UnitBase
{

public:

	// コンストラクタ
	Player(void);

	// デストラクタ
	~Player(void) override;

	//初期化
	void Init(void) override;

	//更新
	void Update(void) override;

	//描画
	void Draw(void) override;

	//解放
	void Release(void) override;

	// モデルの大きさ
	static constexpr VECTOR SCALES = { 0.5f, 0.5f, 0.5f };

	// 初期位置
	static constexpr VECTOR DEFAULT_POS = { 300.0f, 10.0f, 300.0f };

	// 標準の自己発光色
	static constexpr COLOR_F COLOR_EMI_DEFAULT = { 0.5f, 0.5f, 0.5f, 0.5f };

	// 移動スピード
	static constexpr float SPEED_MOVE = 10.0f;

private:
	// モデルID
	int modelId_;
	VECTOR angles_;
	VECTOR scales_;

	//カメラ
	VECTOR axis_;

	// 行動制御
	void ProcessMove(void);
};