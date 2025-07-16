#include "WallAtelier.h"
#include "../../Manager/Generic/ResourceManager.h"

WallAtelier::WallAtelier(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

WallAtelier::~WallAtelier(void)
{
    Release();
}

void WallAtelier::Init(void)
{

    // フェンスの位置を地面に固定（例）
    trans_.pos = { -450.0f, 0.0f, 0.0f };
    trans_.scl = { 2.5f, 2.5f, 2.5f };
    trans_.rot = { 0.0f, 45.0f, 0.0f };
    radius_ = 40;


    isValid_ = true;
}

void WallAtelier::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
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

HitObject::HIT_TYPE WallAtelier::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR WallAtelier::GetHitPosition(void) const
{
    return trans_.pos;
}

float WallAtelier::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
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
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void WallAtelier::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& WallAtelier::GetTransform(void)
{
    return trans_;
}
