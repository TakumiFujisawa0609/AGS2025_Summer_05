#include "WallGuild3.h"
#include "../../Manager/Generic/ResourceManager.h"

WallGuild3::WallGuild3(void)
    : isValid_(false)
{
    const float INITIAL_RADIUS = 50.0f;                 

    radius_ = INITIAL_RADIUS;
}

WallGuild3::~WallGuild3(void)
{
    Release();
}

void WallGuild3::Init(void)
{
    const float POSITION_X = 0.0f;                      // 配置X座標
    const float POSITION_Y = 0.0f;                      // 配置Y座標
    const float POSITION_Z = 450.0f;                    // 配置Z座標
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

void WallGuild3::Update(void)
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

void WallGuild3::Draw(void)
{
}

void WallGuild3::Release(void)
{
    isValid_ = false;
}

VECTOR WallGuild3::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR WallGuild3::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE WallGuild3::GetHitType(void) const
{
    return HIT_TYPE::AABB;
}

VECTOR WallGuild3::GetHitPosition(void) const
{
    return transform_.position;
}

float WallGuild3::GetHitRadius(void) const
{
    return radius_;
}

bool WallGuild3::IsValid(void) const
{
    return isValid_;
}

void WallGuild3::ShowUI(void)
{
}

void WallGuild3::HideUI(void)
{
}

void WallGuild3::OnPlayerHit(void)
{
}

void WallGuild3::OnPlayerExit(void)
{
}

Transform& WallGuild3::GetTransform(void)
{
    return transform_;
}