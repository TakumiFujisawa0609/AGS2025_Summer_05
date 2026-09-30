#include "../Application.h"
#include "../Utility/Utility.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Object/Common/AnimationController.h"
#include "../Object/Manager/CollisionManager.h"
#include "../Manager/Generic/ResourceManager.h"
#include "player.h"

Player::Player(void)
{
    const int INITIAL_VALUE = 0;
    const int INVALID_ID = -1;

    modelHandleId_ = INITIAL_VALUE;
    money_ = INITIAL_VALUE;
    blockedDirectionX_ = INITIAL_VALUE;
    blockedDirectionZ_ = INITIAL_VALUE;
    movementEnabled_ = true;
    currentAnimationType_ = INVALID_ID;

    angles_ = VECTOR();
    scales_ = VECTOR();
}

Player::~Player(void)
{
}

void Player::Init(void)
{
    movementEnabled_ = true;

    modelHandleId_ = ResourceManager::GetInstance().LoadModelDuplicate(
        ResourceManager::SRC::MODEL_PLAYER
    );

    transform_.position = DEFAULT_POSITION;
    previousPosition_ = transform_.position;
    MV1SetPosition(modelHandleId_, transform_.position);

    scales_ = SCALES;
    MV1SetScale(modelHandleId_, scales_);

    radius_ = RADIUS;

    const int MATERIAL_INDEX = 0;
    MV1SetMaterialEmiColor(modelHandleId_, MATERIAL_INDEX, COLOR_EMI_DEFAULT);

    const float ROTATION_ZERO = 0.0f;
    const float ROTATION_HALF_CIRCLE = 180.0f;

    angles_ = {
        ROTATION_ZERO,
        Utility::DegreeToRadianFloat(ROTATION_HALF_CIRCLE),
        ROTATION_ZERO
    };
    MV1SetRotationXYZ(modelHandleId_, angles_);

    animationController_ = new AnimationController(modelHandleId_);

    const float SPEED_IDLE = 35.0f;
    const float SPEED_WALK = 25.0f;

    animationController_->AddExternal(
        static_cast<int>(ANIMATION_TYPE::IDLE),
        Application::PATH_MODEL + "player/Idle.mv1",
        SPEED_IDLE
    );

    animationController_->AddExternal(
        static_cast<int>(ANIMATION_TYPE::WALK),
        Application::PATH_MODEL + "player/Walk.mv1",
        SPEED_WALK
    );

    animationController_->Play(static_cast<int>(ANIMATION_TYPE::IDLE), true);
    currentAnimationType_ = static_cast<int>(ANIMATION_TYPE::IDLE);

    axis_ = { ROTATION_ZERO, ROTATION_ZERO, ROTATION_ZERO };

    const int INITIAL_MONEY = 5000;
    money_ = INITIAL_MONEY;
}

void Player::Update(void)
{
    previousPosition_ = transform_.position;

    animationController_->Update();

    ProcessMove();

    CollisionManager::GetInstance().CheckHitWithPlayer(
        this,
        transform_.position,
        radius_,
        GetHitMin(),
        GetHitMax()
    );
}

void Player::Draw(void)
{
    MV1DrawModel(modelHandleId_);

#ifdef _DEBUG
    const int DRAW_X = 0;
    const int DRAW_Y_POSITION = 40;
    const int DRAW_Y_MONEY = 120;
    const int COLOR_BLACK = 0x0;
    const int COLOR_WHITE = 0xffffff;
    const int SPHERE_DIVISIONS = 16;

    DrawFormatString(
        DRAW_X,
        DRAW_Y_POSITION,
        COLOR_BLACK,
        "プレイヤー座標:(%.2f, %.2f, %.2f)",
        transform_.position.x,
        transform_.position.y,
        transform_.position.z
    );

    DrawSphere3D(
        transform_.position,
        radius_,
        SPHERE_DIVISIONS,
        COLOR_WHITE,
        COLOR_WHITE,
        false
    );

    DrawFormatString(
        DRAW_X,
        DRAW_Y_MONEY,
        COLOR_WHITE,
        "所持金 :%d",
        money_
    );
#endif 
}

void Player::Release(void)
{
    MV1SetScale(transform_.modelId, transform_.scale);
    MV1SetPosition(transform_.modelId, transform_.position);
    MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
    MV1DrawModel(transform_.modelId);

    delete animationController_;
    animationController_ = nullptr;
}

VECTOR Player::GetPosition(void) const
{
    return transform_.position;
}

void Player::SetPosition(VECTOR position)
{
    transform_.position = position;
    MV1SetPosition(modelHandleId_, transform_.position);
}

VECTOR Player::GetHitMin(void) const
{
    return {
        transform_.position.x - radius_,
        transform_.position.y - radius_,
        transform_.position.z - radius_
    };
}

VECTOR Player::GetHitMax(void) const
{
    return {
        transform_.position.x + radius_,
        transform_.position.y + radius_,
        transform_.position.z + radius_
    };
}

float Player::GetRadius(void) const
{
    return radius_;
}

int Player::GetMoney(void) const
{
    return money_;
}

void Player::AddMoney(int money)
{
    money_ += money;
}

void Player::SetBlockedDirectionX(int direction)
{
    blockedDirectionX_ = direction;
}

void Player::SetBlockedDirectionZ(int direction)
{
    blockedDirectionZ_ = direction;
}

void Player::ResetBlockDirections(void)
{
    const int RESET_DIRECTION = 0;
    blockedDirectionX_ = RESET_DIRECTION;
    blockedDirectionZ_ = RESET_DIRECTION;
}

void Player::SetMovementEnabled(bool enabled)
{
    movementEnabled_ = enabled;
    if (!movementEnabled_)
    {
        PlayAnimation(ANIMATION_TYPE::IDLE, true);
    }
}

bool Player::IsMovementEnabled(void) const
{
    return movementEnabled_;
}

void Player::PlayAnimation(ANIMATION_TYPE type, bool loop)
{
    int animationIndex = static_cast<int>(type);

    if (currentAnimationType_ != animationIndex)
    {
        animationController_->Play(animationIndex, loop);
        currentAnimationType_ = animationIndex;
    }
}

void Player::ProcessMove(void)
{
    if (!movementEnabled_)
    {
        return;
    }

    InputManager& inputManager = InputManager::GetInstance();
    ResetBlockDirections();

    VECTOR moveDirection = Utility::VECTOR_ZERO;

    const int DIRECTION_POSITIVE = 1;
    const int DIRECTION_NEGATIVE = -1;

    if (inputManager.IsNew(KEY_INPUT_W) && blockedDirectionZ_ != DIRECTION_POSITIVE)
    {
        moveDirection = VAdd(moveDirection, Utility::DIRECTION_FORWARD);
    }

    if (inputManager.IsNew(KEY_INPUT_S) && blockedDirectionZ_ != DIRECTION_NEGATIVE)
    {
        moveDirection = VAdd(moveDirection, Utility::DIRECTION_BACKWARD);
    }

    if (inputManager.IsNew(KEY_INPUT_A) && blockedDirectionX_ != DIRECTION_POSITIVE)
    {
        moveDirection = VAdd(moveDirection, Utility::DIRECTION_LEFT);
    }

    if (inputManager.IsNew(KEY_INPUT_D) && blockedDirectionX_ != DIRECTION_NEGATIVE)
    {
        moveDirection = VAdd(moveDirection, Utility::DIRECTION_RIGHT);
    }

    if (!Utility::EqualsVZero(moveDirection))
    {
        moveDirection = VNorm(moveDirection);
        VECTOR movementPower = VScale(moveDirection, SPEED_MOVE);
        transform_.position = VAdd(transform_.position, movementPower);

        const float HALF_CIRCLE_DEGREE = 180.0f;
        angles_.y = atan2(moveDirection.x, moveDirection.z) +
            Utility::DegreeToRadianFloat(HALF_CIRCLE_DEGREE);

        MV1SetRotationXYZ(modelHandleId_, angles_);
        MV1SetPosition(modelHandleId_, transform_.position);

        PlayAnimation(ANIMATION_TYPE::WALK);
    }
    else
    {
        PlayAnimation(ANIMATION_TYPE::IDLE);
    }
}