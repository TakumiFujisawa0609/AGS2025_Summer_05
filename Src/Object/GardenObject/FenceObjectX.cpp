#include "FenceObjectX.h"
#include "../../Manager/Generic/ResourceManager.h"

FenceObjectX::FenceObjectX(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

FenceObjectX::~FenceObjectX(void)
{
    Release();
}

void FenceObjectX::Init(void)
{
    auto& res = ResourceManager::GetInstance();
    trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::FENCE_MODEL));

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 0.0f, 0.0f, 0.0f };
    trans_.scl = { 11.5f, 11.5f, 11.5f };
    trans_.rot = { 0.0f, -86.45f, 0.0f };


    isValid_ = true;
}

void FenceObjectX::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void FenceObjectX::Draw(void)
{
    if (trans_.modelId >= 0)
    {
        MV1SetScale(trans_.modelId, trans_.scl);
        MV1SetPosition(trans_.modelId, trans_.pos);
        MV1SetRotationXYZ(trans_.modelId, trans_.rot);
        MV1DrawModel(trans_.modelId);
    }
}

void FenceObjectX::Release(void)
{
    if (trans_.modelId >= 0)
    {
        MV1DeleteModel(trans_.modelId);
        trans_.modelId = -1;
    }
    isValid_ = false;
}

VECTOR FenceObjectX::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR FenceObjectX::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE FenceObjectX::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR FenceObjectX::GetHitPosition(void) const
{
    return trans_.pos;
}

float FenceObjectX::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool FenceObjectX::IsValid(void) const
{
    return isValid_;
}

void FenceObjectX::ShowUI(void)
{
}

void FenceObjectX::HideUI(void)
{
}

void FenceObjectX::OnPlayerHit(void)
{
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void FenceObjectX::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& FenceObjectX::GetTransform(void)
{
    return trans_;
}
