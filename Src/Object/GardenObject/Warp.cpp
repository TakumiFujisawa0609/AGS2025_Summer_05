#include "Warp.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../Object/Manager/AlchemyManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "../../Object/Manager/StageManager.h"
#include "../../DrawUI/SceneUI/TeleportUI.h"

Warp::Warp(StageManager* stageManager)
    : stageManager_(stageManager),
    isShowUI_(false)
{
}

Warp::~Warp(void)
{
}

void Warp::Init(void)
{
    const float ROTATION_ZERO = 0.0f;                   

    auto& resourceManager = ResourceManager::GetInstance();

    transform_.SetModel(resourceManager.LoadModelDuplicate(ResourceManager::SRC::DOOR_MODEL));
    transform_.scale = SCALE;
    radius_ = RADIUS;
    transform_.rotation = { ROTATION_ZERO, DX_PI_F, ROTATION_ZERO };
    isShowUI_ = false;
    transform_.position = MODEL_POSITION;

    if (stageManager_ != nullptr)
    {
        teleportUI_ = std::make_unique<TeleportUI>(
            stageManager_,
            stageManager_->GetPlayer().get()
        );
        teleportUI_->Init();
    }
}

void Warp::Update(void)
{
    auto& inputManager = InputManager::GetInstance();

    if (teleportUI_ != nullptr)
    {
        teleportUI_->Update();
    }

    if (isShowUI_ && inputManager.IsTriggerDown(KEY_INPUT_RETURN))
    {
        SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);

        if (teleportUI_ != nullptr)
        {
            teleportUI_->Show();
            isShowUI_ = false;
        }
    }
}

void Warp::Draw(void)
{
    const int INVALID_MODEL_ID = 0;                     

    if (transform_.modelId >= INVALID_MODEL_ID)
    {
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }

    if (isShowUI_)
    {
        const int FONT_SIZE = 24;                       // フォントサイズ
        const int TEXT_PADDING_WIDTH = 30;              // テキスト背景枠の余白幅
        const int BOX_HEIGHT = 30;                      // 背景ボックスの高さ
        const int SCREEN_HALF_DIVISOR = 2;              // 画面半分除数
        const int BOX_OFFSET_Y = 100;                   // ボックス表示位置Yオフセット
        const int BG_OFFSET_LEFT = 20;                  // 背景左側オフセット
        const int BG_OFFSET_TOP = 10;                   // 背景上部オフセット
        const int BG_EXPAND_RIGHT = 20;                 // 背景右側拡張幅
        const int BG_EXPAND_BOTTOM = 10;                // 背景下部拡張幅
        const int TEXT_OFFSET_INNER_X = 10;             // テキストX内側余白
        const int TEXT_OFFSET_INNER_Y = 5;              // テキストY内側余白
        const int COLOR_BLACK = GetColor(0, 0, 0);      // 黒色
        const int COLOR_WHITE = GetColor(255, 255, 255); // 白色

        const char* text = "移動";
        int textWidth = GetDrawStringWidth(text, static_cast<int>(strlen(text)), FONT_SIZE);
        int boxWidth = textWidth + TEXT_PADDING_WIDTH;
        int boxPositionX = (Application::FULL_SCREEN_SIZE_X - boxWidth) / SCREEN_HALF_DIVISOR;
        int boxPositionY = (Application::FULL_SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR) + BOX_OFFSET_Y;

        DrawBox(
            boxPositionX - BG_OFFSET_LEFT,
            boxPositionY - BG_OFFSET_TOP,
            boxPositionX + boxWidth + BG_EXPAND_RIGHT,
            boxPositionY + BOX_HEIGHT + BG_EXPAND_BOTTOM,
            COLOR_BLACK,
            true
        );
        DrawBox(
            boxPositionX - BG_OFFSET_LEFT,
            boxPositionY - BG_OFFSET_TOP,
            boxPositionX + boxWidth + BG_EXPAND_RIGHT,
            boxPositionY + BOX_HEIGHT + BG_EXPAND_BOTTOM,
            COLOR_WHITE,
            false
        );
        Font::GetInstance().DrawDefaultText(
            boxPositionX + TEXT_OFFSET_INNER_X,
            boxPositionY + TEXT_OFFSET_INNER_Y,
            text,
            COLOR_WHITE,
            FONT_SIZE
        );
    }

    if (teleportUI_ != nullptr)
    {
        teleportUI_->Draw();
    }
}

void Warp::Release(void)
{
}

HitObject::HIT_TYPE Warp::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR Warp::GetHitPosition(void) const
{
    return transform_.position;
}

float Warp::GetHitRadius(void) const
{
    return radius_;
}

void Warp::ShowUI(void)
{
    isShowUI_ = true;
}

void Warp::HideUI(void)
{
    isShowUI_ = false;
}

bool Warp::IsValid(void) const
{
    return true;
}

void Warp::OnPlayerHit(void)
{
    ShowUI();
}

void Warp::OnPlayerExit(void)
{
    HideUI();
}