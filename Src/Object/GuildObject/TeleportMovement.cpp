#include "TeleportMovement.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../Object/Manager/AlchemyManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "../../Object/Manager/StageManager.h"
#include "../../DrawUI/SceneUI/TeleportUI.h"

TeleportMovement::TeleportMovement(StageManager* stageManager)
    : stageManager_(stageManager),
    isShowUI_(false)
{
}

TeleportMovement::~TeleportMovement(void)
{
}

void TeleportMovement::Init(void)
{
    const float ROTATION_ANGLE = 180.0f;                // 向き調整用の回転角（度）

    auto& resourceManager = ResourceManager::GetInstance();

    transform_.SetModel(resourceManager.LoadModelDuplicate(ResourceManager::SRC::BULLETIN_BOARD));
    transform_.quaternionRotation = Quaternion();
    transform_.quaternionRotationLocal = Quaternion::AngleAxis(
        Utility::DegreeToRadianFloat(ROTATION_ANGLE),
        Utility::AXIS_Y
    );
    transform_.scale = SCALE;
    radius_ = RADIUS;
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

void TeleportMovement::Update(void)
{
    auto& inputManager = InputManager::GetInstance();

    if (teleportUI_ != nullptr)
    {
        teleportUI_->Update();
    }

    if (isShowUI_ && inputManager.IsTriggerDown(KEY_INPUT_RETURN))
    {
        if (teleportUI_ != nullptr)
        {
            Application::GetInstance().SetActiveUIType(Application::ACTIVE_UI_TYPE::TELEPORT);
            teleportUI_->Show();
        }
    }
}

void TeleportMovement::Draw(void)
{
    if (transform_.modelId != -1)
    {
        MV1DrawModel(transform_.modelId);
    }

    const int screenWidth = Application::FULL_SCREEN_SIZE_X;
    const int screenHeight = Application::FULL_SCREEN_SIZE_Y;

    if (isShowUI_)
    {
        const int FONT_SIZE = 24;                       // フォントサイズ
        const int TEXT_PADDING_WIDTH = 30;              // テキスト背景枠の余白幅
        const int BOX_HEIGHT = 30;                      // 背景ボックスの高さ
        const int BOX_OFFSET_Y = 100;                   // ボックス表示位置Yオフセット
        const int BG_OFFSET_LEFT = 20;                  // 背景左側オフセット
        const int BG_OFFSET_TOP = 10;                   // 背景上部オフセット
        const int BG_EXPAND_RIGHT = 20;                 // 背景右側拡張幅
        const int BG_EXPAND_BOTTOM = 10;                // 背景下部拡張幅
        const int TEXT_OFFSET_INNER = 5;                // ボックス内テキスト余白
        const int COLOR_BLACK = GetColor(0, 0, 0);      // 黒色
        const int COLOR_WHITE = GetColor(255, 255, 255); // 白色

        const char* text = "移動";
        int textWidth = GetDrawStringWidth(text, static_cast<int>(strlen(text)), FONT_SIZE);
        int boxWidth = textWidth + TEXT_PADDING_WIDTH;
        int boxPositionX = (screenWidth - boxWidth) / 2;
        int boxPositionY = (screenHeight / 2) + BOX_OFFSET_Y;

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
            boxPositionX + TEXT_OFFSET_INNER,
            boxPositionY + TEXT_OFFSET_INNER,
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

void TeleportMovement::Release(void)
{
}

HitObject::HIT_TYPE TeleportMovement::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR TeleportMovement::GetHitPosition(void) const
{
    return transform_.position;
}

float TeleportMovement::GetHitRadius(void) const
{
    return radius_;
}

void TeleportMovement::ShowUI(void)
{
    isShowUI_ = true;
}

void TeleportMovement::HideUI(void)
{
    isShowUI_ = false;

    if (teleportUI_ != nullptr)
    {
        teleportUI_->Hide();
    }
}

bool TeleportMovement::IsValid(void) const
{
    return true;
}

void TeleportMovement::OnPlayerHit(void)
{
    ShowUI();
}

void TeleportMovement::OnPlayerExit(void)
{
    HideUI();
}