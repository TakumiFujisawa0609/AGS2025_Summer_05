#include "WallGuild4.h"
#include "../../Manager/Generic/ResourceManager.h"

WallGuild4::WallGuild4(void)
    : isValid_(false)
{
    const float INITIAL_RADIUS = 50.0f;                 // 初期当たり判定半径

    radius_ = INITIAL_RADIUS;
}

WallGuild4::~WallGuild4(void)
{
    Release();
}

void WallGuild4::Init(void)
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

void WallGuild4::Update(void)
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

void WallGuild4::Draw(void)
{
}

void WallGuild4::Release(void)
{
    isValid_ = false;
}

VECTOR WallGuild4::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR WallGuild4::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE WallGuild4::GetHitType(void) const
{
    return HIT_TYPE::AABB;
}

VECTOR WallGuild4::GetHitPosition(void) const
{
    return transform_.position;
}

float WallGuild4::GetHitRadius(void) const
{
    return radius_;
}

bool WallGuild4::IsValid(void) const
{
    return isValid_;
}

void WallGuild4::ShowUI(void)
{
}

void WallGuild4::HideUI(void)
{
}

void WallGuild4::OnPlayerHit(void)
{
}

void WallGuild4::OnPlayerExit(void)
{
}

Transform& WallGuild4::GetTransform(void)
{
    return transform_;
}