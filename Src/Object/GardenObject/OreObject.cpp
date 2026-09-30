#include "OreObject.h"

#include <DxLib.h>
#include <random>

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/System/TimeManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../DrawUI/Font.h"
#include "../Manager/ItemManager.h"
#include "../../Application.h"

OreObject::OreObject(void)
    : radius_(40.0f),
    isUIVisible_(false),
    wantsToShowUI_(false),
    isOnCooldown_(false),
    cooldownState_(COOL_DOWNSTATE::READY),
    minedTime_(0.0f),
    modelId_(-1)
{
}

OreObject::~OreObject(void)
{
    const int INVALID_MODEL_ID = 0;                     

    if (modelId_ >= INVALID_MODEL_ID)
    {
        MV1DeleteModel(modelId_);
    }
}

void OreObject::Init(void)
{
    const float MODEL_SCALE = 0.03f;                    // モデルの描画スケール
    const float ROTATION_ZERO = 0.0f;                   // 回転角のゼロ値

    modelId_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::ORE_MODEL);
    transform_.modelId = modelId_;
    transform_.scale = VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
    transform_.rotation = VGet(ROTATION_ZERO, ROTATION_ZERO, ROTATION_ZERO);
}

void OreObject::Update(void)
{
    if (isOnCooldown_)
    {
        if (TimeManager::GetInstance().GetGameTime() - minedTime_ >= ORE_COOLDOWN_TIME)
        {
            isOnCooldown_ = false;
            cooldownState_ = COOL_DOWNSTATE::READY;
        }
        else
        {
            cooldownState_ = COOL_DOWNSTATE::COOLINGDOWN;
        }
    }
    else
    {
        cooldownState_ = COOL_DOWNSTATE::READY;
    }

    auto& inputManager = InputManager::GetInstance();

    if (isUIVisible_ && (inputManager.IsTriggerDown(KEY_INPUT_RETURN) ||
        inputManager.IsTriggerDown(KEY_INPUT_NUMPADENTER)))
    {
        SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);

        if (cooldownState_ == COOL_DOWNSTATE::READY)
        {
            TryMine();
        }
    }
}

void OreObject::Draw(void)
{
    const int INVALID_MODEL_ID = 0;                     

    if (modelId_ >= INVALID_MODEL_ID)
    {
        MV1SetPosition(modelId_, transform_.position);
        MV1SetScale(modelId_, transform_.scale);
        MV1SetRotationXYZ(modelId_, transform_.rotation);
        MV1DrawModel(modelId_);
    }

    if (isUIVisible_)
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
        const int TEXT_OFFSET_INNER = 5;                // ボックス内テキスト余白
        const int COLOR_BLACK = GetColor(0, 0, 0);      // 黒色
        const int COLOR_WHITE = GetColor(255, 255, 255); // 白色

        const char* text = nullptr;

        if (cooldownState_ == COOL_DOWNSTATE::READY)
        {
            text = "採掘";
        }
        else if (cooldownState_ == COOL_DOWNSTATE::COOLINGDOWN)
        {
            text = "採掘不可";
        }

        const int screenWidth = Application::SCREEN_SIZE_X;
        const int screenHeight = Application::SCREEN_SIZE_Y;

        int textWidth = GetDrawStringWidth(text, static_cast<int>(strlen(text)), FONT_SIZE);
        int boxWidth = textWidth + TEXT_PADDING_WIDTH;

        int boxPositionX = screenWidth / SCREEN_HALF_DIVISOR - boxWidth / SCREEN_HALF_DIVISOR;
        int boxPositionY = screenHeight / SCREEN_HALF_DIVISOR + BOX_OFFSET_Y;

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

#ifdef _DEBUG
    const int SPHERE_DIVISIONS = 8;                     // 球体の分割数
    const int COLOR_GREEN = GetColor(0, 255, 0);        // 緑色

    DrawSphere3D(
        transform_.position,
        radius_,
        SPHERE_DIVISIONS,
        COLOR_GREEN,
        COLOR_GREEN,
        false
    );
#endif
}

void OreObject::Release(void)
{
}

void OreObject::TryMine(void)
{
    if (cooldownState_ != COOL_DOWNSTATE::READY)
    {
        return;
    }

    const int ADD_AMOUNT = 1;                           

    auto ironOreItem = std::dynamic_pointer_cast<MaterialItem>(
        ItemManager::GetInstance().FindItemById("IronOre")
    );

    if (ironOreItem != nullptr)
    {
        ItemManager::GetInstance().AddQuantity(ironOreItem, ADD_AMOUNT);
    }

    std::vector<std::string> materials = {
        "FireMagicStone",
        "WaterMagicStone",
        "WindMagicStone",
        "EarthMagicStone",
        "IceMagicStone",
        "LightMagicStone",
        "DarkMagicStone"
    };

    if (!materials.empty())
    {
        const int MIN_INDEX = 0;                        
        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());
        std::uniform_int_distribution<> distribution(
            MIN_INDEX,
            static_cast<int>(materials.size()) - 1
        );

        int index = distribution(generator);

        auto magicStoneItem = std::dynamic_pointer_cast<MaterialItem>(
            ItemManager::GetInstance().FindItemById(materials[index])
        );

        if (magicStoneItem != nullptr)
        {
            ItemManager::GetInstance().AddQuantity(magicStoneItem, ADD_AMOUNT);
        }
    }

    StartCooldown();
    HideUI();
}

void OreObject::StartCooldown(void)
{
    minedTime_ = TimeManager::GetInstance().GetGameTime();
    isOnCooldown_ = true;
    cooldownState_ = COOL_DOWNSTATE::COOLINGDOWN;
}

bool OreObject::IsCooldownOver(void) const
{
    if (isOnCooldown_)
    {
        return (TimeManager::GetInstance().GetGameTime() - minedTime_ >= ORE_COOLDOWN_TIME);
    }

    return false;
}

OreObject::HIT_TYPE OreObject::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR OreObject::GetHitPosition(void) const
{
    return transform_.position;
}

float OreObject::GetHitRadius(void) const
{
    return radius_;
}

bool OreObject::IsValid(void) const
{
    return true;
}

void OreObject::OnPlayerHit(void)
{
    isUIVisible_ = true;
}

void OreObject::ShowUI(void)
{
    isUIVisible_ = true;
}

void OreObject::HideUI(void)
{
    isUIVisible_ = false;
}

void OreObject::OnPlayerExit(void)
{
    HideUI();
}

Transform& OreObject::GetTransform(void)
{
    return transform_;
}