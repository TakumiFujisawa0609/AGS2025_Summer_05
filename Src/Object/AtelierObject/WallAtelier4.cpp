#include "WallAtelier4.h"
#include "../../Manager/Generic/ResourceManager.h"

WallAtelier4::WallAtelier4(void)
    : isValid_(false)
{
    const float INITIAL_RADIUS = 50.0f;                 

    radius_ = INITIAL_RADIUS;
}

WallAtelier4::~WallAtelier4(void)
{
    Release();
}

void WallAtelier4::Init(void)
{
    const float POSITION_X = 0.0f;                      // 配置X座標
    const float POSITION_Y = 0.0f;                      // 配置Y座標
    const float POSITION_Z = -450.0f;                   // 配置Z座標
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

void WallAtelier4::Update(void)
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

void WallAtelier4::Draw(void)
{
}

void WallAtelier4::Release(void)
{
    isValid_ = false;
}

VECTOR WallAtelier4::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR WallAtelier4::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE WallAtelier4::GetHitType(void) const
{
    return HIT_TYPE::AABB;
}

VECTOR WallAtelier4::GetHitPosition(void) const
{
    return transform_.position;
}

float WallAtelier4::GetHitRadius(void) const
{
    return radius_;
}

bool WallAtelier4::IsValid(void) const
{
    return isValid_;
}

void WallAtelier4::ShowUI(void)
{
}

void WallAtelier4::HideUI(void)
{
}

void WallAtelier4::OnPlayerHit(void)
{
}

void WallAtelier4::OnPlayerExit(void)
{
}

Transform& WallAtelier4::GetTransform(void)
{
    return transform_;
}