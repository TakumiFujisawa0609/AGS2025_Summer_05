#include " WallGuild2.h"
#include "../../Manager/Generic/ResourceManager.h"

WallGuild2::WallGuild2(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

WallGuild2::~WallGuild2(void)
{
    Release();
}

void WallGuild2::Init(void)
{

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 450.0f, 0.0f, 0.0f };
    trans_.scl = { 2.5f, 2.5f, 2.5f };
    trans_.rot = { 0.0f, 45.0f, 0.0f };
    radius_ = 40;


    isValid_ = true;
}

void  WallGuild2::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void  WallGuild2::Draw(void)
{
}

void  WallGuild2::Release(void)
{
    isValid_ = false;
}

VECTOR  WallGuild2::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR  WallGuild2::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE  WallGuild2::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR WallGuild2::GetHitPosition(void) const
{
    return trans_.pos;
}

float  WallGuild2::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool WallGuild2::IsValid(void) const
{
    return isValid_;
}

void  WallGuild2::ShowUI(void)
{
}

void  WallGuild2::HideUI(void)
{
}

void  WallGuild2::OnPlayerHit(void)
{
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void WallGuild2::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& WallGuild2::GetTransform(void)
{
    return trans_;
}
