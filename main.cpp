#include <DxLib.h>
#include "player.h"

Player player_;

// 関数の前方宣言
// -----------------------------------------------------------
// // 初期処理
void Init(void);
// 更新処理
void Update(void);
// 描画処理
void Draw(void);
// 解放処理
void Release(void);
// -----------------------------------------------------------
// WinMain関数
//------------------------------------------------------------
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	// ウィンドウサイズ
	SetGraphMode(1024, 768, 32);
	ChangeWindowMode(true);

	// DxLibの初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//初期処理
	Init();

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Update();

		
		Draw();
		

		// 描画スクリーンの切替
		ScreenFlip();
	}

	Release();

	// DxLibの後始末
	if (DxLib_End() == -1)
	{
		return -1;
	}
	return 0;
}

void Init(void)
{
	player_.Init();
}

void Update(void)
{
	player_.Update();
}

void Draw(void)
{
	// 描画スクリーンの設定
	SetDrawScreen(DX_SCREEN_BACK);
	// 描画スクリーンを初期化
	ClearDrawScreen();
	player_.Draw();
	//プレイヤー座標の描画
	VECTOR playerPos = player_.GetPos();
	DrawFormatString(0, 60, 0xffffff, "プレイヤー座標：(%.2f,%.2f,%.2f)", playerPos.x, playerPos.y, playerPos.z);
}

void Release(void)
{
	player_.Release();
}