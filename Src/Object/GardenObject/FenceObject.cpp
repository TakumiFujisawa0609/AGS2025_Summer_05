#include "FenceObject.h"
#include "../../Manager/Generic/ResourceManager.h"

FenceObject::FenceObject(void)
    : isValid_(false)
{
    const float INITIAL_RADIUS = 50.0f;                 

    radius_ = INITIAL_RADIUS;
}

FenceObject::~FenceObject(void)
{
    Release();
}

void FenceObject::Init(void)
{
    const float POSITION_X = 0.0f;                      // 配置X座標
    const float POSITION_Y = 0.0f;                      // 配置Y座標
    const float POSITION_Z = 0.0f;                      // 配置Z座標
    const float MODEL_SCALE = 11.5f;                    // モデルの描画スケール
    const float ROTATION_ZERO = 0.0f;                   // 回転角のゼロ値
    const float ACTUAL_RADIUS = 40.0f;                  // 実質的な当たり判定半径（AABBのため未使用）

    auto& resourceManager = ResourceManager::GetInstance();
    transform_.SetModel(resourceManager.LoadModelDuplicate(ResourceManager::SRC::FENCE_MODEL));

    transform_.position = { POSITION_X, POSITION_Y, POSITION_Z };
    transform_.scale = { MODEL_SCALE, MODEL_SCALE, MODEL_SCALE };
    transform_.rotation = { ROTATION_ZERO, ROTATION_ZERO, ROTATION_ZERO };
    radius_ = ACTUAL_RADIUS;

    isValid_ = true;
}

void FenceObject::Update(void)
{
    const float HALF_DIVISOR = 2.0f;                    

    hitMin_ = {
        transform_.position.x - WIDTH / HALF_DIVISOR,
        transform_.position.y - HEIGHT / HALF_DIVISOR,
        transform_.position.z - DEPTH / HALF_DIVISOR
    };

    hitMax_ = {
        transform_.position.x + WIDTH / HALF_DIVISOR,
        transform_.position.y + HEIGHT / HALF_DIVISOR,
        transform_.position.z + DEPTH / HALF_DIVISOR
    };
}

void FenceObject::Draw(void)
{
    const int INVALID_MODEL_ID = 0;                     

    if (transform_.modelId >= INVALID_MODEL_ID)
    {
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }
}

void FenceObject::Release(void)
{
    const int INVALID_MODEL_ID = 0;                     // 有効モデルIDの下限境界

    if (transform_.modelId >= INVALID_MODEL_ID)
    {
        MV1DeleteModel(transform_.modelId);
        transform_.modelId = -1;
    }

    isValid_ = false;
}

VECTOR FenceObject::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR FenceObject::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE FenceObject::GetHitType(void) const
{
    return HIT_TYPE::AABB;
}

VECTOR FenceObject::GetHitPosition(void) const
{
    return transform_.position;
}

float FenceObject::GetHitRadius(void) const
{
    return radius_;
}

bool FenceObject::IsValid(void) const
{
    return isValid_;
}

void FenceObject::ShowUI(void)
{
}

void FenceObject::HideUI(void)
{
}

void FenceObject::OnPlayerHit(void)
{
}

void FenceObject::OnPlayerExit(void)
{
}

Transform& FenceObject::GetTransform(void)
{
    return transform_;
}