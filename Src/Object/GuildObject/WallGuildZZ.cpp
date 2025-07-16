#include "WallGuildZZ.h"
#include "../../Manager/Generic/ResourceManager.h"

WallGuildZZ::WallGuildZZ(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

WallGuildZZ::~WallGuildZZ(void)
{
    Release();
}

void WallGuildZZ::Init(void)
{

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 0.0f, 0.0f, -450.0f };
    trans_.scl = { 2.5f, 2.5f, 2.5f };
    trans_.rot = { 0.0f, 45.0f, 0.0f };
    radius_ = 40;


    isValid_ = true;
}

void WallGuildZZ::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void WallGuildZZ::Draw(void)
{
}

void WallGuildZZ::Release(void)
{
    isValid_ = false;
}

VECTOR WallGuildZZ::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR WallGuildZZ::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE WallGuildZZ::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR WallGuildZZ::GetHitPosition(void) const
{
    return trans_.pos;
}

float WallGuildZZ::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool WallGuildZZ::IsValid(void) const
{
    return isValid_;
}

void WallGuildZZ::ShowUI(void)
{
}

void WallGuildZZ::HideUI(void)
{
}

void WallGuildZZ::OnPlayerHit(void)
{
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void WallGuildZZ::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& WallGuildZZ::GetTransform(void)
{
    return trans_;
}
