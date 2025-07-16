#include " WallGuildZ.h"
#include "../../Manager/Generic/ResourceManager.h"

WallGuildZ::WallGuildZ(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

WallGuildZ::~WallGuildZ(void)
{
    Release();
}

void WallGuildZ::Init(void)
{

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 0.0f, 0.0f, 450.0f };
    trans_.scl = { 2.5f, 2.5f, 2.5f };
    trans_.rot = { 0.0f, 45.0f, 0.0f };
    radius_ = 40;


    isValid_ = true;
}

void  WallGuildZ::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void  WallGuildZ::Draw(void)
{
}

void  WallGuildZ::Release(void)
{
    isValid_ = false;
}

VECTOR  WallGuildZ::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR  WallGuildZ::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE  WallGuildZ::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR WallGuildZ::GetHitPosition(void) const
{
    return trans_.pos;
}

float  WallGuildZ::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool WallGuildZ::IsValid(void) const
{
    return isValid_;
}

void  WallGuildZ::ShowUI(void)
{
}

void  WallGuildZ::HideUI(void)
{
}

void  WallGuildZ::OnPlayerHit(void)
{
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void  WallGuildZ::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& WallGuildZ::GetTransform(void)
{
    return trans_;
}
