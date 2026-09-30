#include "Application.h"

#include <DxLib.h>
#include <EffekseerForDXLib.h>

#include "Manager/Decoration/EffectManager.h"
#include "Manager/Generic/ResourceManager.h"
#include "Manager/Generic/InputManager.h"
#include "Manager/Generic/SceneManager.h"
#include "Object/Manager/AlchemyManager.h"
#include "DrawUI/SceneUI/QuestUI.h"
#include "DrawUI/Font.h"
#include "Fps/FpsControll.h"
#include "DrawUI/SceneUI/PauseMenu.h"
#include "Scene/SceneTitle.h"

Application* Application::instance_ = nullptr;

const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_ANIMATION = "Data/Anim/";
const std::string Application::PATH_EFFECT = "Data/Effect/";
const std::string Application::PATH_TEXT = "Data/Text/";
const std::string Application::PATH_FONT = "Data/Font/";
const std::string Application::PATH_JSON = "Data/Json/";
const std::string Application::PATH_BGM = "Data/Sound/BGM/";
const std::string Application::PATH_SE = "Data/Sound/SE/";
const std::string Application::PATH_MOVIE = "Data/Movie/";
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
    SetWindowText("アルケミストライフ");

    const int COLOR_BIT_DEPTH = 32;
    SetGraphMode(DEFAULT_SCREEN_SIZE_X, DEFAULT_SCREEN_SIZE_Y, COLOR_BIT_DEPTH);

    ChangeWindowMode(false);
    SetAlwaysRunFlag(true);

    fps_->FpsControll_Initialize();

    SetUseDirect3DVersion(DX_DIRECT3D_11);
    isInitializeFailed_ = false;

    const int DXLIB_ERROR = -1;
    if (DxLib_Init() == DXLIB_ERROR)
    {
        isInitializeFailed_ = true;
        return;
    }

    SetMouseDispFlag(FALSE);

    InitEffekseer();

    SetUseDirectInputFlag(true);
    InputManager::CreateInstance();
    ResourceManager::CreateInstance();
    SceneManager::CreateInstance();
    AlchemyManager::CreateInstance();
    QuestUI::CreateInstance();
    Font::CreateInstance();
    EffectManager::CreateInstance();

    std::string fontPath = Application::PATH_FONT + "NikkyouSans-mLKax.ttf";

    const int FONT_SIZE = 24;
    const int FONT_THICKNESS = 6;

    Font::GetInstance().AddFont(
        "GameFont",
        "Nikkyou Sans",
        fontPath,
        FONT_SIZE,
        FONT_THICKNESS,
        Font::FONT_TYPE_EDGE
    );

    pauseMenu_ = new PauseMenu();
    pauseMenu_->Init();

    activeUIType_ = ACTIVE_UI_TYPE::NONE;
}

void Application::Run(void)
{
    auto& inputManager = InputManager::GetInstance();
    auto& sceneManager = SceneManager::GetInstance();

    MSG message;

    const int PROCESS_SUCCESS = 0;

    while (ProcessMessage() == PROCESS_SUCCESS)
    {
        const UINT MESSAGE_FILTER_MIN = 0;
        const UINT MESSAGE_FILTER_MAX = 0;

        if (PeekMessage(&message, NULL, MESSAGE_FILTER_MIN, MESSAGE_FILTER_MAX, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        const int SLEEP_TIME = 1;
        Sleep(SLEEP_TIME);

        fps_->FpsControll_Update();

        if (isActiveUI_ == false)
        {
            const int INPUT_PRESSED = 1;

            if (!pauseMenu_->IsVisible() &&
                inputManager.IsTriggerDown(KEY_INPUT_ESCAPE) == INPUT_PRESSED)
            {
                pauseMenu_->Show();
            }
        }

        inputManager.Update();

        if (pauseMenu_->IsVisible())
        {
            pauseMenu_->Update();

            if (pauseMenu_->IsDecisionMade())
            {
                int selectedIndex = pauseMenu_->GetSelectedIndex();

                const int MENU_CONTINUE = 0;
                const int MENU_HOW_TO_PLAY = 1;
                const int MENU_CONTROLS = 2;
                const int MENU_EXIT = 3;

                switch (selectedIndex)
                {
                case MENU_CONTINUE:
                    pauseMenu_->Hide();
                    break;

                case MENU_HOW_TO_PLAY:
                    // TODO: Help UI表示
                    break;

                case MENU_CONTROLS:
                    // TODO: 操作説明 UI表示
                    break;

                case MENU_EXIT:
                    return;
                }
            }
        }
        else
        {
            sceneManager.Update();
            QuestUI::GetInstance().Update();

            auto titleScene = dynamic_cast<SceneTitle*>(sceneManager.GetScene());
            if (titleScene != nullptr && titleScene->IsExitRequested())
            {
                return;
            }
        }

        UpdateEffekseer3D();

        sceneManager.Draw();
        fps_->FpsControll_Draw();
        DrawEffekseer3D();

        if (pauseMenu_->IsVisible())
        {
            pauseMenu_->Draw();
        }

        ScreenFlip();
        fps_->FpsControll_Wait();
    }
}

void Application::Destroy(void)
{
    InputManager::GetInstance().Destroy();
    ResourceManager::GetInstance().Destroy();
    SceneManager::GetInstance().Destroy();
    AlchemyManager::GetInstance().Destroy();
    Font::GetInstance().Destroy();
    QuestUI::Destroy();
    EffectManager::GetInstance().Destroy();

    Effkseer_End();

    const int DXLIB_ERROR = -1;
    if (DxLib_End() == DXLIB_ERROR)
    {
        isReleaseFailed_ = true;
    }

    delete fps_;
    delete instance_;
}

bool Application::IsInitializeFailed(void) const
{
    return isInitializeFailed_;
}

bool Application::IsReleaseFailed(void) const
{
    return isReleaseFailed_;
}

bool Application::IsActiveUI(void) const
{
    return isActiveUI_;
}

void Application::SetActiveUI(bool isActive)
{
    isActiveUI_ = isActive;
}

void Application::SetActiveUIType(ACTIVE_UI_TYPE uiType)
{
    activeUIType_ = uiType;
}

bool Application::IsTeleportUIActive(void) const
{
    return activeUIType_ == ACTIVE_UI_TYPE::TELEPORT;
}

Application::ACTIVE_UI_TYPE Application::GetActiveUIType(void) const
{
    return activeUIType_;
}

void Application::InitEffekseer(void)
{
    const int MAX_PARTICLES = 8000;
    const int DXLIB_ERROR = -1;

    if (Effekseer_Init(MAX_PARTICLES) == DXLIB_ERROR)
    {
        DxLib_End();
    }

    SetChangeScreenModeGraphicsSystemResetFlag(false);
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();
}

Application::Application(void)
{
    fps_ = new Fps();

    isInitializeFailed_ = false;
    isReleaseFailed_ = false;
    isActiveUI_ = false;

    activeUIType_ = ACTIVE_UI_TYPE::NONE;
}