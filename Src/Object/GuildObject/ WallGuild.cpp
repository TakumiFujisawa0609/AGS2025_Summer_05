#include " WallGuild.h"
#include "../../Manager/Generic/ResourceManager.h"

WallGuild::WallGuild(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

WallGuild::~WallGuild(void)
{
    Release();
}

void WallGuild::Init(void)
{

    // フェンスの位置を地面に固定（例）
    trans_.pos = { -450.0f, 0.0f, 0.0f };
    trans_.scl = { 2.5f, 2.5f, 2.5f };
    trans_.rot = { 0.0f, 45.0f, 0.0f };
    radius_ = 40;


    isValid_ = true;
}

void WallGuild::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void WallGuild::Draw(void)
{
}

void WallGuild::Release(void)
{
    isValid_ = false;
}

VECTOR WallGuild::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR WallGuild::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE WallGuild::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR WallGuild::GetHitPosition(void) const
{
    return trans_.pos;
}

float WallGuild::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool WallGuild::IsValid(void) const
{
    return isValid_;
}

void WallGuild::ShowUI(void)
{
}

void WallGuild::HideUI(void)
{
}

void WallGuild::OnPlayerHit(void)
{
}

void WallGuild::OnPlayerExit(void)
{
}

Transform& WallGuild::GetTransform(void)
{
    return trans_;
}
