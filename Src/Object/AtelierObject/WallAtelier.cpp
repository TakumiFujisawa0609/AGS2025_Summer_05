#include "WallAtelier.h"
#include "../../Manager/Generic/ResourceManager.h"

WallAtelier::WallAtelier(void)
    : isValid_(false)
{
    const float INITIAL_RADIUS = 50.0f;                 

    radius_ = INITIAL_RADIUS;
}

WallAtelier::~WallAtelier(void)
{
    Release();
}

void WallAtelier::Init(void)
{
    const float POSITION_X = -450.0f;                   // 配置X座標
    const float POSITION_Y = 0.0f;                      // 配置Y座標
    const float POSITION_Z = 0.0f;                      // 配置Z座標
    const float MODEL_SCALE = 2.5f;                     // モデルの描画スケール
    const float ROTATION_X = 0.0f;                      // 回転角X
    const float ROTATION_Y = 45.0f;                     // 回転角Y
    const float ROTATION_Z = 0.0f;                      // 回転角Z
    const float ACTUAL_RADIUS = 40.0f;                  // 実質的な当たり判定半径（AABBのため未使用）

    transform_.position = { POSITION_X, POSITION_Y, POSITION_Z };
    transform_.scale = { MODEL_SCALE, MODEL_SCALE, MODEL_SCALE };
    transform_.rotation = { ROTATION_X, ROTATION_Y, ROTATION_Z };
    radius_ = ACTUAL_RADIUS;

    isValid_ = true;
}

void WallAtelier::Update(void)
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

void WallAtelier::Draw(void)
{
}

void WallAtelier::Release(void)
{
    isValid_ = false;
}

VECTOR WallAtelier::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR WallAtelier::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE WallAtelier::GetHitType(void) const
{
    return HIT_TYPE::AABB;
}

VECTOR WallAtelier::GetHitPosition(void) const
{
    return transform_.position;
}

float WallAtelier::GetHitRadius(void) const
{
    return radius_;
}

bool WallAtelier::IsValid(void) const
{
    return isValid_;
}

void WallAtelier::ShowUI(void)
{
}

void WallAtelier::HideUI(void)
{
}

void WallAtelier::OnPlayerHit(void)
{
}

void WallAtelier::OnPlayerExit(void)
{
}

Transform& WallAtelier::GetTransform(void)
{
    return transform_;
}