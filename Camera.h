#pragma once
#include <DxLib.h>
class Camera
{
public:

	//初期化
	void Init(void);

	//更新
	void Update(void);

	//描画前のカメラ設定
	void SetBeforeDraw(void);

	//描画
	void Draw(void);

	//解放
	void Release(void);

	//カメラ位置
	VECTOR GetPos(void);

	// カメラの初期位置
	static constexpr VECTOR INIT_POS = { 0.0f, 300.0f, -600.0f };

private:

	// カメラ位置
	VECTOR pos_;
};