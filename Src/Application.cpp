#include"Application.h"

#include<DxLib.h>
#include<EffekseerForDXLib.h>

#include "Manager/Generic/ResourceManager.h"
#include "Manager/Generic/InputManager.h"
#include "Manager/Generic/SceneManager.h"
#include "Object/Manager/ItemManager.h"
#include "Object/Manager/AlchemyManager.h"
#include "DrawUI/SceneUI/QuestUI.h"
#include "DrawUI/Font.h"
#include "Fps/FpsControll.h"


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
const std::string Application::PATH_MAP_DATA = "Data/MapData/MapData.csv";

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
	SetWindowText("アルケミストライフ");
	
	//ウィンドウのサイズ
	SetGraphMode(DEFA_SCREEN_SIZE_X, DEFA_SCREEN_SZIE_Y, 32);

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
	ResourceManager::CreateInstance();

	// シーン管理初期化
	SceneManager::CreateInstance();

	//アイテムマネージャー初期化
	ItemManager::CreateInstance();

	//錬金システムの初期化
	AlchemyManager::CreateInstance();

	//QuestUI初期化を追加
	QuestUI::CreateInstance();

	//フォントの初期化
	Font::CreateInstance();

	//FPS制御初期化
	fps_->FpsControll_Initialize();
}

void Application::Run(void)
{
	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

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

		//FPS制御更新処理
		fps_->FpsControll_Update();

		//ESCAPEキーが押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			return;
		}
		//更新処理
		inputManager.Update();
		sceneManager.Update();
		// QuestUI更新
		QuestUI::GetInstance().Update();
		
		//描画処理
		sceneManager.Draw();
		// QuestUI描画（最後に描画して他のUIより前面に表示）
		QuestUI::GetInstance().Draw();

		if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_TAB) == 1)
		{
			fps_->FpsControll_Draw();
		}
		//フロントバッファに書き出し
		ScreenFlip();


		//FPS制御
		fps_->FpsControll_Wait();
		
	}
}

void Application::Destroy(void)
{
	InputManager::GetInstance().Destroy();
	ResourceManager::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	ItemManager::GetInstance().Destroy();
	AlchemyManager::GetInstance().Destroy();
	Font::GetInstance().Destroy();
	// QuestUI終了処理
	QuestUI::Destroy();

	//エフェクシアの終了
	Effkseer_End();

	//DXLibの終了
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}
	
	delete fps_;
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
	fps_ = new Fps();
	isInitFail_ = false;
	isReleaseFail_ = false;
}