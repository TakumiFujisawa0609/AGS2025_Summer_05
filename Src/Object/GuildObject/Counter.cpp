#include "Counter.h"
#include "../../Manager/Generic/ResourceManager.h"

Counter::Counter(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

Counter::~Counter(void)
{
    Release();
}

void Counter::Init(void)
{
    trans_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::COUNTER);

    // フェンスの位置を地面に固定（例）
    trans_.pos = { -150.0f, 0.0f, 200.0f };
    trans_.scl = { 0.1f, 0.05f, 0.15f };
    trans_.rot = { 0.0f, -105.3f, 0.0f };
    radius_ = RADIUS;


    isValid_ = true;
}

void  Counter::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void  Counter::Draw(void)
{
    if (trans_.modelId >= 0)
    {
        MV1SetScale(trans_.modelId, trans_.scl);
        MV1SetPosition(trans_.modelId, trans_.pos);
        MV1SetRotationXYZ(trans_.modelId, trans_.rot);
        MV1DrawModel(trans_.modelId);
    }
}

void  Counter::Release(void)
{
    isValid_ = false;
}

VECTOR  Counter::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR  Counter::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE  Counter::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR Counter::GetHitPosition(void) const
{
    return trans_.pos;
}

float  Counter::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool Counter::IsValid(void) const
{
    return isValid_;
}

void  Counter::ShowUI(void)
{
}

void Counter::HideUI(void)
{
}

void  Counter::OnPlayerHit(void)
{
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void  Counter::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& Counter::GetTransform(void)
{
    return trans_;
}
