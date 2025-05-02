#pragma once
#include<DxLib.h>
class Player
{
public:

	//初期化
	void Init(void);

	//更新
	void Update(void);

	//描画
	void Draw(void);

	//解放
	void Release(void);

	//位置
	VECTOR GetPos(void);

	//生存判定の取得
	bool IsAlive(void);

	//生存判定の更新
	void SetAlive(bool isAlive);

	// 初期位置
	static constexpr VECTOR INIT_POS = { 0.0f, 60.0f, 0.0f };
	// 移動量(横)
	static constexpr float MOVE_POW_X = 10.0f;
	// 移動量(縦)
	static constexpr float MOVE_POW_Y = 10.0f;
	// 移動量(前進)
	static constexpr float MOVE_POW_Z = 20.0f;
	// 移動制限
	static constexpr float MOVE_LIMIT = 400.0f;
	// 衝突判定用半径
	static constexpr float RADIUS = 80.0f;

private:
	// モデルID
	int ModelId_;
	// 位置
	VECTOR pos_;
	// 生存判定
	bool isAlive_;
};