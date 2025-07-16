#include "WallAtelier2.h"
#include "../../Manager/Generic/ResourceManager.h"

WallAtelier2::WallAtelier2(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

WallAtelier2::~WallAtelier2(void)
{
    Release();
}

void WallAtelier2::Init(void)
{

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 450.0f, 0.0f, 0.0f };
    trans_.scl = { 2.5f, 2.5f, 2.5f };
    trans_.rot = { 0.0f, 45.0f, 0.0f };
    radius_ = 40;


    isValid_ = true;
}

void WallAtelier2::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void WallAtelier2::Draw(void)
{
}

void WallAtelier2::Release(void)
{
    isValid_ = false;
}

VECTOR WallAtelier2::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR WallAtelier2::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE WallAtelier2::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR WallAtelier2::GetHitPosition(void) const
{
    return trans_.pos;
}

float WallAtelier2::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool WallAtelier2::IsValid(void) const
{
    return isValid_;
}

void WallAtelier2::ShowUI(void)
{
}

void WallAtelier2::HideUI(void)
{
}

void WallAtelier2::OnPlayerHit(void)
{
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void WallAtelier2::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& WallAtelier2::GetTransform(void)
{
    return trans_;
}
