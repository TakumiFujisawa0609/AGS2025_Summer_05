#include "WallAtelierZZ.h"
#include "../../Manager/Generic/ResourceManager.h"

WallAtelierZZ::WallAtelierZZ(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

WallAtelierZZ::~WallAtelierZZ(void)
{
    Release();
}

void WallAtelierZZ::Init(void)
{

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 0.0f, 0.0f, -450.0f };
    trans_.scl = { 2.5f, 2.5f, 2.5f };
    trans_.rot = { 0.0f, 45.0f, 0.0f };
    radius_ = 40;


    isValid_ = true;
}

void WallAtelierZZ::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void WallAtelierZZ::Draw(void)
{
}

void WallAtelierZZ::Release(void)
{
    isValid_ = false;
}

VECTOR WallAtelierZZ::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR WallAtelierZZ::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE WallAtelierZZ::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR WallAtelierZZ::GetHitPosition(void) const
{
    return trans_.pos;
}

float WallAtelierZZ::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool WallAtelierZZ::IsValid(void) const
{
    return isValid_;
}

void WallAtelierZZ::ShowUI(void)
{
}

void WallAtelierZZ::HideUI(void)
{
}

void WallAtelierZZ::OnPlayerHit(void)
{
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void WallAtelierZZ::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& WallAtelierZZ::GetTransform(void)
{
    return trans_;
}
