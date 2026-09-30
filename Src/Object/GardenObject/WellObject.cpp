#include "WellObject.h"
#include <DxLib.h>
#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/System/TimeManager.h"
#include "../../Object/Manager/ItemManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"

WellObject::WellObject(void)
    : isUIVisible_(false),
    wantsToShowUI_(false),
    isOnCooldown_(false),
    minedTime_(0.0f)
{
}

WellObject::~WellObject(void)
{
    Release();
}

void WellObject::Init(void)
{
    transform_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(
        ResourceManager::SRC::WELL_MODEL
    );
    transform_.position = MODEL_POSITION;
    transform_.scale = MODEL_SCALE;
    transform_.rotation = MODEL_ROTATION;
}

void WellObject::Update(void)
{
    if (isOnCooldown_ && IsCooldownOver())
    {
        isOnCooldown_ = false;
    }

    isUIVisible_ = wantsToShowUI_;

    auto& inputManager = InputManager::GetInstance();

    if (isUIVisible_ && (inputManager.IsTriggerDown(KEY_INPUT_RETURN) ||
        inputManager.IsTriggerDown(KEY_INPUT_NUMPADENTER)))
    {
        SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);

        if (!isOnCooldown_)
        {
            TryDrawWater();
        }
    }
}

void WellObject::Draw(void)
{
    if (transform_.modelId >= 0)
    {
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }

    if (isUIVisible_)
    {
        const int FONT_SIZE = 24;                           // フォントサイズ
        const int BOX_PADDING_WIDTH = 30;                   // テキスト背景枠の余白幅
        const int BOX_HEIGHT = 30;                          // 背景ボックスの高さ
        const int BOX_OFFSET_Y = 100;                       // ボックス表示位置Yオフセット
        const int BG_OFFSET_LEFT = 10;                      // 背景左側オフセット
        const int BG_OFFSET_TOP = 10;                       // 背景上部オフセット
        const int BG_EXPAND_RIGHT = 20;                     // 背景右側拡張幅
        const int BG_EXPAND_BOTTOM = 10;                    // 背景下部拡張幅
        const int TEXT_OFFSET_INNER = 5;                    // ボックス内テキスト余白
        const int COLOR_BLACK = GetColor(0, 0, 0);          // 黒色
        const int COLOR_WHITE = GetColor(255, 255, 255);    // 白色

        const char* text = isOnCooldown_ ? "汲めない" : "水を汲む";

        int textWidth = GetDrawStringWidth(text, static_cast<int>(strlen(text)), FONT_SIZE);
        int boxWidth = textWidth + BOX_PADDING_WIDTH;

        int boxX = (Application::SCREEN_SIZE_X / 2) - boxWidth / 2;
        int boxY = (Application::SCREEN_SIZE_Y / 2) + BOX_OFFSET_Y;

        DrawBox(
            boxX - BG_OFFSET_LEFT,
            boxY - BG_OFFSET_TOP,
            boxX + boxWidth + BG_EXPAND_RIGHT,
            boxY + BOX_HEIGHT + BG_EXPAND_BOTTOM,
            COLOR_BLACK,
            true
        );
        DrawBox(
            boxX - BG_OFFSET_LEFT,
            boxY - BG_OFFSET_TOP,
            boxX + boxWidth + BG_EXPAND_RIGHT,
            boxY + BOX_HEIGHT + BG_EXPAND_BOTTOM,
            COLOR_WHITE,
            false
        );
        Font::GetInstance().DrawDefaultText(
            boxX + TEXT_OFFSET_INNER,
            boxY + TEXT_OFFSET_INNER,
            text,
            COLOR_WHITE,
            FONT_SIZE
        );
    }

#ifdef _DEBUG
    const int SPHERE_DIVISIONS = 8;                     // 球体の分割数
    const int COLOR_BLUE = GetColor(0, 0, 255);         // 青色

    DrawSphere3D(
        transform_.position,
        RADIUS,
        SPHERE_DIVISIONS,
        COLOR_BLUE,
        COLOR_BLUE,
        false
    );
#endif
}

void WellObject::Release(void)
{
    if (transform_.modelId >= 0)
    {
        MV1DeleteModel(transform_.modelId);
        transform_.modelId = -1;
    }
}

Transform& WellObject::GetTransform(void)
{
    return transform_;
}

bool WellObject::IsCooldownOver(void) const
{
    return TimeManager::GetInstance().GetGameTime() - minedTime_ >= COOLDOWN_TIME;
}

void WellObject::StartCooldown(void)
{
    minedTime_ = TimeManager::GetInstance().GetGameTime();
    isOnCooldown_ = true;
}

void WellObject::TryDrawWater(void)
{
    const int WATER_DRAW_AMOUNT = 5;

    auto waterItem = std::dynamic_pointer_cast<MaterialItem>(
        ItemManager::GetInstance().FindItemById("Water")
    );

    if (waterItem != nullptr)
    {
        ItemManager::GetInstance().AddQuantity(waterItem, WATER_DRAW_AMOUNT);
    }

    StartCooldown();
    HideUI();
}

HitObject::HIT_TYPE WellObject::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR WellObject::GetHitPosition(void) const
{
    return transform_.position;
}

float WellObject::GetHitRadius(void) const
{
    return RADIUS;
}

bool WellObject::IsValid(void) const
{
    return true;
}

void WellObject::ShowUI(void)
{
    wantsToShowUI_ = true;
}

void WellObject::HideUI(void)
{
    wantsToShowUI_ = false;
    isUIVisible_ = false;
}

void WellObject::OnPlayerHit(void)
{
    ShowUI();
}

void WellObject::OnPlayerExit(void)
{
    HideUI();
}