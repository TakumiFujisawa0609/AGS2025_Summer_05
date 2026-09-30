#include "AlchemyPot.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../Object/Manager/AlchemyManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "../Player.h"

AlchemyPot::AlchemyPot(void)
{
    isShowUserInterface_ = false;
}

AlchemyPot::~AlchemyPot(void)
{
}

void AlchemyPot::SetPlayer(std::shared_ptr<Player> player)
{
    player_ = player;
}

void AlchemyPot::Init(void)
{
    auto& resourceManager = ResourceManager::GetInstance();
    transform_.SetModel(resourceManager.LoadModelDuplicate(ResourceManager::SRC::ALCHEMYPOT));

    radius_ = RADIUS;
    isShowUserInterface_ = false;

    transform_.position = MODEL_POSITION;
    transform_.scale = MODEL_SCALE;

    const float ROTATION_ZERO = 0.0f;
    transform_.rotation = { ROTATION_ZERO, ROTATION_ZERO, ROTATION_ZERO };
}

void AlchemyPot::Update(void)
{
    auto& inputManager = InputManager::GetInstance();
    auto& alchemyManager = AlchemyManager::GetInstance();

    const int INPUT_PRESSED = 1;

    if (isShowUserInterface_ && inputManager.IsTriggerDown(KEY_INPUT_RETURN) == INPUT_PRESSED)
    {
        Application::GetInstance().SetActiveUI(true);
        SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);

        if (!alchemyManager.IsOpen())
        {
            alchemyManager.Open();
        }
    }

    if (alchemyManager.IsOpen())
    {
        alchemyManager.Update();
        isShowUserInterface_ = false;
    }
}

void AlchemyPot::Draw(void)
{
    auto& alchemyManager = AlchemyManager::GetInstance();

    const int INVALID_MODEL_ID = -1;

    if (transform_.modelId > INVALID_MODEL_ID)
    {
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }

    const int SCREEN_WIDTH = Application::FULL_SCREEN_SIZE_X;
    const int SCREEN_HEIGHT = Application::FULL_SCREEN_SIZE_Y;

    if (alchemyManager.IsOpen())
    {
        alchemyManager.Draw();
    }

    if (isShowUserInterface_)
    {
        const char* TEXT = "˜B‹à";
        const int FONT_SIZE = 24;
        const int TEXT_MARGIN = 30;
        const int BOX_HEIGHT = 30;

        int textWidth = GetDrawStringWidth(TEXT, static_cast<int>(strlen(TEXT)), FONT_SIZE);
        int boxWidth = textWidth + TEXT_MARGIN;

        const int HALF_DIVISOR = 2;
        const int Y_OFFSET = 100;

        int boxX = (SCREEN_WIDTH - boxWidth) / HALF_DIVISOR;
        int boxY = SCREEN_HEIGHT / HALF_DIVISOR + Y_OFFSET;

        const int BOX_MARGIN_X = 20;
        const int BOX_MARGIN_Y = 10;

        const int COLOR_BLACK = GetColor(0, 0, 0);
        const int COLOR_WHITE = GetColor(255, 255, 255);

        DrawBox(
            boxX - BOX_MARGIN_X,
            boxY - BOX_MARGIN_Y,
            boxX + boxWidth + BOX_MARGIN_X,
            boxY + BOX_HEIGHT + BOX_MARGIN_Y,
            COLOR_BLACK,
            true
        );

        DrawBox(
            boxX - BOX_MARGIN_X,
            boxY - BOX_MARGIN_Y,
            boxX + boxWidth + BOX_MARGIN_X,
            boxY + BOX_HEIGHT + BOX_MARGIN_Y,
            COLOR_WHITE,
            false
        );

        const int TEXT_OFFSET = 5;

        Font::GetInstance().DrawDefaultText(
            boxX + TEXT_OFFSET,
            boxY + TEXT_OFFSET,
            TEXT,
            COLOR_WHITE,
            FONT_SIZE
        );
    }
}

void AlchemyPot::Release(void)
{
}

HitObject::HIT_TYPE AlchemyPot::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR AlchemyPot::GetHitPosition(void) const
{
    return transform_.position;
}

float AlchemyPot::GetHitRadius(void) const
{
    return radius_;
}

void AlchemyPot::ShowUI(void)
{
    isShowUserInterface_ = true;
}

void AlchemyPot::HideUI(void)
{
    isShowUserInterface_ = false;
    AlchemyManager::GetInstance().Close();
}

bool AlchemyPot::IsValid(void) const
{
    return true;
}

void AlchemyPot::OnPlayerHit(void)
{
    ShowUI();
    VECTOR playerPosition = player_->GetPosition();
}

void AlchemyPot::OnPlayerExit(void)
{
    HideUI();
}

bool AlchemyPot::IsOpen(void) const
{
    return AlchemyManager::GetInstance().IsOpen();
}