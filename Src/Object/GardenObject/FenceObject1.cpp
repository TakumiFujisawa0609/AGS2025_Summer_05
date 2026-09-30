#include "FenceObject1.h"
#include "../../Manager/Generic/ResourceManager.h"

FenceObject1::FenceObject1(void)
    : isValid_(false)
{
    const float INITIAL_RADIUS = 50.0f;                 // 初期当たり判定半径

    radius_ = INITIAL_RADIUS;
}

FenceObject1::~FenceObject1(void)
{
    Release();
}

void FenceObject1::Init(void)
{
    const float POSITION_X = 0.0f;                      // 配置X座標
    const float POSITION_Y = 0.0f;                      // 配置Y座標
    const float POSITION_Z = 0.0f;                      // 配置Z座標
    const float MODEL_SCALE = 11.5f;                    // モデルの描画スケール
    const float ROTATION_X = 0.0f;                      // 回転角X
    const float ROTATION_Y = -86.45f;                   // 回転角Y
    const float ROTATION_Z = 0.0f;                      // 回転角Z
    const float ACTUAL_RADIUS = 40.0f;                  // 実質的な当たり判定半径（AABBのため未使用）

    auto& resourceManager = ResourceManager::GetInstance();
    transform_.SetModel(resourceManager.LoadModelDuplicate(ResourceManager::SRC::FENCE_MODEL));

    transform_.position = { POSITION_X, POSITION_Y, POSITION_Z };
    transform_.scale = { MODEL_SCALE, MODEL_SCALE, MODEL_SCALE };
    transform_.rotation = { ROTATION_X, ROTATION_Y, ROTATION_Z };
    radius_ = ACTUAL_RADIUS;

    isValid_ = true;
}

void FenceObject1::Update(void)
{
    const float HALF_DIVISOR = 2.0f;                    // 中心から端までの長さを求める除数

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

void FenceObject1::Draw(void)
{
    const int INVALID_MODEL_ID = 0;                     // 有効モデルIDの下限境界

    if (transform_.modelId >= INVALID_MODEL_ID)
    {
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }
}

void FenceObject1::Release(void)
{
    const int INVALID_MODEL_ID = 0;                     // 有効モデルIDの下限境界
    const int RESET_MODEL_ID = -1;                      // リセット用の無効値

    if (transform_.modelId >= INVALID_MODEL_ID)
    {
        MV1DeleteModel(transform_.modelId);
        transform_.modelId = RESET_MODEL_ID;
    }

    isValid_ = false;
}

VECTOR FenceObject1::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR FenceObject1::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE FenceObject1::GetHitType(void) const
{
    return HIT_TYPE::AABB;
}

VECTOR FenceObject1::GetHitPosition(void) const
{
    return transform_.position;
}

float FenceObject1::GetHitRadius(void) const
{
    return radius_;
}

bool FenceObject1::IsValid(void) const
{
    return isValid_;
}

void FenceObject1::ShowUI(void)
{
}

void FenceObject1::HideUI(void)
{
}

void FenceObject1::OnPlayerHit(void)
{
}

void FenceObject1::OnPlayerExit(void)
{
}

Transform& FenceObject1::GetTransform(void)
{
    return transform_;
}