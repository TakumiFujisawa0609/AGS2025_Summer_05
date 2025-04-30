#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"Manager/Generic/InputManager.h"
#include"Application.h"

Application* Application::instance_ = nullptr;

//ファイル指定パス
const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_ANIM = "Data/Anim/";
const std::string Application::PATH_EFFECT = "Data/Effect/";
const std::string Application::PATH_TEXT = "Data/Text/";
const std::string Application::PATH_FONT = "Data/Font/";
const std::string Application::PATH_BGM = "Data/Sound/BGM/";
const std::string Application::PATH_SE = "Data/Sound/SE/";

void Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
		instance_->Init();
	}
}

Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::Init(void)
{
	//アプリケーションの初期設定
	SetWindowText("タイトルを記入");
	
	//ウィンドウのサイズ
	SetGraphMode(SCREEN_SIZE_X,	SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	//非アクティブ状態でも動作する
	SetAlwaysRunFlag(TRUE);

	//DXLibの初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		//エラー処理
		isInitFail_ = true;
		return;
	}

	//エフェクシアの初期化
	InitEffekseer();

	// キー制御初期化
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();

	//リソース管理初期化

	//FPS用初期化
	currentFrame_ = 0;
	lastFrame_ = 0;
}

void Application::Run(void)
{
	MSG msg;

	//ゲームループ
	while (ProcessMessage() == 0)
	{
		//メッセージループ
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		//システムに処理を返す
		Sleep(1);

		//現在のフレームを取得
		currentFrame_ = GetNowCount();

		//現在の時刻が、前回の時刻より
		//1/60秒以上経過していたら処理を実行する
		if (currentFrame_ - lastFrame_ >= FRAME_RATE)
		{
			//フレーム実行時の時間を更新
			lastFrame_ = currentFrame_;

			//フレーム数のカウント
			frameCnt_++;

			//ESCAPEキーが押されたら終了
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				return;
			}

			//更新処理


			//描画処理

			//フレームレートの計算
			CalcFrameRate();

			//フレームレートの表示(Debug用)
			DrawFrameRate();

			//フロントバッファに書き出し
			ScreenFlip();
		}
	}
}

void Application::Destroy(void)
{
	//エフェクシアの終了
	Effkseer_End();

	//DXLibの終了
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}
	
	delete instance_;
}

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}

void Application::InitEffekseer(void)
{
	if (Effekseer_Init(8000) == 1)
	{
		DxLib_End();
	}
	SetChangeScreenModeGraphicsSystemResetFlag(false);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

}

Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
}

void Application::CalcFrameRate()
{
	//前回のフレームレート更新からの経過時間を求める
	int nDifTime = currentFrame_ - updateFrameRateTime_;

	//前回のフレーム更新から
	//1秒以上経過していたらフレームレートを更新する
	if (nDifTime >= 1000)
	{
		
	}
}
