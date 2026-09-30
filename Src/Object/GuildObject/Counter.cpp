#include "Counter.h"
#include "../../Manager/Generic/ResourceManager.h"

Counter::Counter(void)
    : isValid_(false)
{
    radius_ = RADIUS;
}

Counter::~Counter(void)
{
    Release();
}

void Counter::Init(void)
{
    const float POSITION_X = -150.0f;                   // 配置X座標
    const float POSITION_Y = 0.0f;                      // 配置Y座標
    const float POSITION_Z = 200.0f;                    // 配置Z座標
    const float MODEL_SCALE_X = 0.1f;                   // モデルスケールX
    const float MODEL_SCALE_Y = 0.05f;                  // モデルスケールY
    const float MODEL_SCALE_Z = 0.15f;                  // モデルスケールZ
    const float ROTATION_X = 0.0f;                      // 回転角X
    const float ROTATION_Y = -105.3f;                   // 回転角Y
    const float ROTATION_Z = 0.0f;                      // 回転角Z

    transform_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(
        ResourceManager::SRC::COUNTER
    );

    transform_.position = { POSITION_X, POSITION_Y, POSITION_Z };
    transform_.scale = { MODEL_SCALE_X, MODEL_SCALE_Y, MODEL_SCALE_Z };
    transform_.rotation = { ROTATION_X, ROTATION_Y, ROTATION_Z };
    radius_ = RADIUS;

    isValid_ = true;
}

void Counter::Update(void)
{
    hitMin_ = {
        transform_.position.x - WIDTH / 2,
        transform_.position.y - HEIGHT / 2,
        transform_.position.z - DEPTH / 2
    };

    hitMax_ = {
        transform_.position.x + WIDTH / 2,
        transform_.position.y + HEIGHT / 2,
        transform_.position.z + DEPTH / 2
    };
}

void Counter::Draw(void)
{
    if (transform_.modelId >= 0)
    {
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }
}

void Counter::Release(void)
{
    isValid_ = false;
}

VECTOR Counter::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR Counter::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE Counter::GetHitType(void) const
{
    return HIT_TYPE::AABB;
}

VECTOR Counter::GetHitPosition(void) const
{
    return transform_.position;
}

float Counter::GetHitRadius(void) const
{
    return radius_;
}

bool Counter::IsValid(void) const
{
    return isValid_;
}

void Counter::ShowUI(void)
{
}

void Counter::HideUI(void)
{
}

void Counter::OnPlayerHit(void)
{
}

void Counter::OnPlayerExit(void)
{
}

Transform& Counter::GetTransform(void)
{
    return transform_;
}