#include "Bookshelf.h"

#include "../../Manager/Generic/ResourceManager.h"

Bookshelf::Bookshelf(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

Bookshelf::~Bookshelf(void)
{
    Release();
}

void Bookshelf::Init(void)
{
    auto& res = ResourceManager::GetInstance();
    trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::BOOKS_HELF));

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 300.0f, 0.0f, 200.0f };
    trans_.scl = { 2.5f, 2.5f, 2.5f };
    trans_.rot = { 0.0f, 0.0f, 0.0f };

    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };

    isValid_ = true;
}

void Bookshelf::Update(void)
{
    
}

void Bookshelf::Draw(void)
{
    if (trans_.modelId >= 0)
    {
        MV1SetScale(trans_.modelId, trans_.scl);
        MV1SetPosition(trans_.modelId, trans_.pos);
        MV1SetRotationXYZ(trans_.modelId, trans_.rot);
        MV1DrawModel(trans_.modelId);
    }
}

void Bookshelf::Release(void)
{
    if (trans_.modelId >= 0)
    {
        MV1DeleteModel(trans_.modelId);
        trans_.modelId = -1;
    }
    isValid_ = false;
}

VECTOR Bookshelf::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR Bookshelf::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE Bookshelf::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR Bookshelf::GetHitPosition(void) const
{
    return trans_.pos;
}

float Bookshelf::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool Bookshelf::IsValid(void) const
{
    return isValid_;
}

void Bookshelf::ShowUI(void)
{
}

void Bookshelf::HideUI(void)
{
}

void Bookshelf::OnPlayerHit(void)
{
    
}

void Bookshelf::OnPlayerExit(void)
{
   
}

Transform& Bookshelf::GetTransform(void)
{
    return trans_;
}
