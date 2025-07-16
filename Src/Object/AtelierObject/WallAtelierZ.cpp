#include "WallAtelierZ.h"
#include "../../Manager/Generic/ResourceManager.h"

WallAtelierZ::WallAtelierZ(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

WallAtelierZ::~WallAtelierZ(void)
{
    Release();
}

void WallAtelierZ::Init(void)
{

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 0.0f, 0.0f, 450.0f };
    trans_.scl = { 2.5f, 2.5f, 2.5f };
    trans_.rot = { 0.0f, 45.0f, 0.0f };
    radius_ = 40;


    isValid_ = true;
}

void WallAtelierZ::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void WallAtelierZ::Draw(void)
{
}

void WallAtelierZ::Release(void)
{
    isValid_ = false;
}

VECTOR WallAtelierZ::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR WallAtelierZ::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE WallAtelierZ::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR WallAtelierZ::GetHitPosition(void) const
{
    return trans_.pos;
}

float WallAtelierZ::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool WallAtelierZ::IsValid(void) const
{
    return isValid_;
}

void WallAtelierZ::ShowUI(void)
{
}

void WallAtelierZ::HideUI(void)
{
}

void WallAtelierZ::OnPlayerHit(void)
{
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void WallAtelierZ::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& WallAtelierZ::GetTransform(void)
{
    return trans_;
}
