#pragma once
#include<DxLib.h>
class Player
{
public:

	// コンストラクタ
	Player(void);

	// デストラクタ
	~Player(void);

	//初期化
	void Init(void);

	//更新
	void Update(void);

	//描画
	void Draw(void);

	//解放
	void Release(void);	

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
	VECTOR pos_;
	VECTOR angles_;
	VECTOR scales_;

	// 行動制御
	void ProcessMove(void);
};