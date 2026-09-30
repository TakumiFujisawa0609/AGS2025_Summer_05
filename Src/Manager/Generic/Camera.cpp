#include "Camera.h"

#include <EffekseerForDXLib.h>

#include "../../Application.h"
#include "../../Utility/Utility.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "../../Object/Common/Transform.h"

Camera::Camera(void)
{
    mode_ = MODE::NONE;
    position_ = Utility::VECTOR_ZERO;
    targetPosition_ = Utility::VECTOR_ZERO;
    rotation_ = Quaternion::Identity();
}

Camera::~Camera(void)
{
}

void Camera::Init(void)
{
    setBeforeDrawMode_.emplace(MODE::NONE,
        std::bind(&Camera::SetBeforeDrawFollow, this));
    setBeforeDrawMode_.emplace(MODE::FIXED_POINT,
        std::bind(&Camera::SetBeforeDrawFixedPoint, this));
    setBeforeDrawMode_.emplace(MODE::FREE,
        std::bind(&Camera::SetBeforeDrawFree, this));
    setBeforeDrawMode_.emplace(MODE::FOLLOW,
        std::bind(&Camera::SetBeforeDrawFollow, this));
    setBeforeDrawMode_.emplace(MODE::FOLLOW_SPRING,
        std::bind(&Camera::SetBeforeDrawFollowSpring, this));
    setBeforeDrawMode_.emplace(MODE::FOLLOW_PERSPECTIVE,
        std::bind(&Camera::SetBeforeDrawFollowPerspective, this));
    setBeforeDrawMode_.emplace(MODE::SHAKE,
        std::bind(&Camera::SetBeforeDrawShake, this));

    SetDefault();
    SetLighting();
}

void Camera::Update(void)
{
    SetLightPositionHandle(spotLightHandle_, position_);
    SetLightDirectionHandle(spotLightHandle_, rotation_.ToEuler());
}

void Camera::SetBeforeDraw(void)
{
    SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

    setBeforeDrawMode_[mode_]();

    SetCameraPositionAndTargetAndUpVec(
        position_,
        targetPosition_,
        cameraUp_
    );

    Effekseer_Sync3DSetting();
}

void Camera::SetBeforeDrawFixedPoint(void)
{
}

void Camera::SetBeforeDrawFree(void)
{
    auto& inputManager = InputManager::GetInstance();

    ProcessMove();
    Decelerate(MOVE_DECELERATION);
    Move();
}

void Camera::SetBeforeDrawFollow(void)
{
    VECTOR followPosition = followTransform_->position;
    Quaternion followRotation = followTransform_->quaternionRotation;

    VECTOR relativeCameraPosition = followRotation.PosAxis(
        RELATIVE_FOLLOW_TO_CAMERA_POSITION);

    position_ = VAdd(followPosition, relativeCameraPosition);

    VECTOR relativeTargetPosition = followRotation.PosAxis(
        RELATIVE_CAMERA_TO_TARGET_POSITION);

    targetPosition_ = VAdd(position_, relativeTargetPosition);
    cameraUp_ = followRotation.PosAxis(rotation_.GetUp());
}

void Camera::SetBeforeDrawFollowSpring(void)
{
    auto& inputManager = InputManager::GetInstance();

    if (inputManager.IsTriggerDown(KEY_INPUT_C))
    {
        currentMode_ = mode_;
        ChangeMode(MODE::SHAKE);
    }

    // 計算用ローカル定数
    const float SPRING_POWER = 50.0f;
    const float DAMPENING = 2.0f * sqrt(SPRING_POWER);

    float deltaTime = SceneManager::GetInstance().GetDeltaTime();

    VECTOR followPosition = followTransform_->position;
    Quaternion followRotation = followTransform_->quaternionRotation;

    const VECTOR ZERO_VECTOR = { 0.0f, 0.0f, 0.0f };
    Quaternion forwardRotation = Quaternion::Euler(ZERO_VECTOR);

    VECTOR relativeCameraPosition = forwardRotation.PosAxis(
        RELATIVE_FOLLOW_TO_CAMERA_POSITION);

    VECTOR idealPosition = VAdd(followPosition, relativeCameraPosition);
    VECTOR positionDifference = VSub(position_, idealPosition);

    VECTOR springForce = VScale(positionDifference, -SPRING_POWER);
    springForce = VSub(springForce, VScale(velocity_, DAMPENING));

    velocity_ = VAdd(position_, VScale(velocity_, deltaTime));
    position_ = VAdd(position_, VScale(velocity_, deltaTime));

    VECTOR relativeTargetPosition = forwardRotation.PosAxis(
        RELATIVE_CAMERA_TO_TARGET_POSITION);

    targetPosition_ = VAdd(position_, relativeTargetPosition);
    cameraUp_ = forwardRotation.PosAxis(rotation_.GetUp());
}

void Camera::SetBeforeDrawFollowPerspective(void)
{
    VECTOR followPosition = followTransform_->position;
    Quaternion followRotation = followTransform_->quaternionRotation;

    VECTOR relativeTargetPosition = followRotation.PosAxis(
        RELATIVE_CAMERA_TO_TARGET_POSITION_PERSPECTIVE);

    targetPosition_ = VAdd(position_, relativeTargetPosition);
    cameraUp_ = followRotation.PosAxis(rotation_.GetUp());
}

void Camera::SetBeforeDrawShake(void)
{
    shakeTimer_ -= SceneManager::GetInstance().GetDeltaTime();

    if (shakeTimer_ < 0.0f)
    {
        position_ = defaultPosition_;
        ChangeMode(MODE::FOLLOW_SPRING);
        return;
    }

    const float AMPLIFIER = 1000.0f;
    float shakeFactor = sinf(shakeTimer_ * SHAKE_SPEED) * AMPLIFIER;

    int shakeInteger = static_cast<int>(shakeFactor);
    int shakeSign = shakeInteger % 2;
    shakeSign *= 2;
    shakeSign -= 1;

    VECTOR velocity = VScale(
        shakeDirection_,
        static_cast<float>(shakeSign) * SHAKE_WIDTH
    );

    position_ = VAdd(defaultPosition_, velocity);
}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
    SetLightEnableHandle(spotLightHandle_, false);
    DeleteLightHandle(spotLightHandle_);
}

VECTOR Camera::GetPosition(void) const
{
    return position_;
}

void Camera::ChangeMode(MODE mode)
{
    mode_ = mode;

    switch (mode_)
    {
    case MODE::FIXED_POINT:
        break;

    case MODE::FREE:
        break;

    case MODE::FOLLOW:
        break;

    case MODE::FOLLOW_SPRING:
        break;

    case MODE::SHAKE:
        const VECTOR SHAKE_BASE_DIRECTION = { 0.7f, 0.7f, 0.0f };

        shakeTimer_ = SHAKE_TIME;
        shakeDirection_ = VNorm(SHAKE_BASE_DIRECTION);
        defaultPosition_ = position_;
        break;
    }
}

void Camera::SetFollow(const Transform* follow)
{
    followTransform_ = follow;
}

void Camera::SetPosition(const VECTOR& position, const VECTOR& targetPosition)
{
    position_ = position;
    targetPosition_ = targetPosition;
}

VECTOR Camera::GetFrontVector(void) const
{
    VECTOR frontVector = VSub(targetPosition_, position_);
    float length = sqrtf(
        frontVector.x * frontVector.x +
        frontVector.y * frontVector.y +
        frontVector.z * frontVector.z
    );

    if (length > 0.0001f)
    {
        frontVector.x /= length;
        frontVector.y /= length;
        frontVector.z /= length;
    }

    return frontVector;
}

void Camera::SetDefault(void)
{
    position_ = DEFAULT_CAMERA_POSITION;
    targetPosition_ = VAdd(position_, RELATIVE_CAMERA_TO_TARGET_POSITION);
    cameraUp_ = { 0.0f, 1.0f, 0.0f };
    rotation_ = Quaternion::Identity();
    velocity_ = Utility::VECTOR_ZERO;
}

void Camera::SetLighting(void)
{
    spotLightHandle_ = CreateSpotLightHandle(
        position_,
        VGet(0.0f, -1.0f, 0.0f),
        DX_PI_F / 2.0f,
        DX_PI_F / 4.0f,
        2000.0f,
        0.0f,
        0.002f,
        0.0f
    );

    SetLightEnableHandle(spotLightHandle_, true);
}

void Camera::ProcessMove(void)
{
    auto& inputManager = InputManager::GetInstance();

    if (inputManager.IsNew(KEY_INPUT_W))
    {
        moveDirection_ = Utility::DIRECTION_FORWARD;
        Acceleration(MOVE_ACCELERATION);
    }

    if (inputManager.IsNew(KEY_INPUT_S))
    {
        moveDirection_ = Utility::DIRECTION_BACKWARD;
        Acceleration(MOVE_ACCELERATION);
    }

    if (inputManager.IsNew(KEY_INPUT_A))
    {
        moveDirection_ = Utility::DIRECTION_LEFT;
        Acceleration(MOVE_ACCELERATION);
    }

    if (inputManager.IsNew(KEY_INPUT_D))
    {
        moveDirection_ = Utility::DIRECTION_RIGHT;
        Acceleration(MOVE_ACCELERATION);
    }

    VECTOR axisDegree = Utility::VECTOR_ZERO;

    if (inputManager.IsNew(KEY_INPUT_UP))
    {
        axisDegree.x = -1.0f;
    }

    if (inputManager.IsNew(KEY_INPUT_DOWN))
    {
        axisDegree.x = 1.0f;
    }

    if (inputManager.IsNew(KEY_INPUT_LEFT))
    {
        axisDegree.y = -1.0f;
    }

    if (inputManager.IsNew(KEY_INPUT_RIGHT))
    {
        axisDegree.y = 1.0f;
    }

    if (!Utility::EqualsVZero(axisDegree))
    {
        Quaternion rotationPower;

        rotationPower = rotationPower.Mult(
            Quaternion::AngleAxis(Utility::DegreeToRadianFloat(axisDegree.z), Utility::AXIS_Z)
        );

        rotationPower = rotationPower.Mult(
            Quaternion::AngleAxis(Utility::DegreeToRadianFloat(axisDegree.x), Utility::AXIS_X)
        );

        rotationPower = rotationPower.Mult(
            Quaternion::AngleAxis(Utility::DegreeToRadianFloat(axisDegree.y), Utility::AXIS_Y)
        );

        rotation_ = rotation_.Mult(rotationPower);

        VECTOR rotatedLocalPosition = rotation_.PosAxis(
            RELATIVE_CAMERA_TO_TARGET_POSITION);

        targetPosition_ = VAdd(position_, rotatedLocalPosition);
        cameraUp_ = rotation_.GetUp();
    }
}

void Camera::Move(void)
{
    if (Utility::EqualsVZero(moveDirection_))
    {
        VECTOR direction = rotation_.PosAxis(moveDirection_);
        VECTOR movementVector = VScale(direction, moveSpeed_);

        position_ = VAdd(position_, movementVector);
        targetPosition_ = VAdd(targetPosition_, movementVector);
    }
}

void Camera::Acceleration(float speed)
{
    moveSpeed_ += speed;

    if (moveSpeed_ > MAX_MOVE_SPEED)
    {
        moveSpeed_ = MAX_MOVE_SPEED;
    }

    if (moveSpeed_ < -MAX_MOVE_SPEED)
    {
        moveSpeed_ = -MAX_MOVE_SPEED;
    }
}

void Camera::Decelerate(float speed)
{
    if (moveSpeed_ > 0.0f)
    {
        moveSpeed_ -= speed;

        if (moveSpeed_ < 0.0f)
        {
            moveSpeed_ = 0.0f;
        }
    }

    if (moveSpeed_ < 0.0f)
    {
        moveSpeed_ += speed;

        if (moveSpeed_ > 0.0f)
        {
            moveSpeed_ = speed;
        }
    }
}