#include "TableSetGuild.h"

#include "../../Manager/Generic/ResourceManager.h"

TableSetGuild::TableSetGuild(void)
    : isValid_(false)
{
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

TableSetGuild::~TableSetGuild(void)
{
    Release();
}

void TableSetGuild::Init(void)
{
    trans_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::TABLE_SET);

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 0.0f, 0.0f, 0.0f };
    trans_.scl = { 0.07f, 0.07f, 0.07f };
    trans_.rot = { 0.0f, 0.0f, 0.0f };
    radius_ = RADIUS;


    isValid_ = true;
}

void TableSetGuild::Update(void)
{
    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };
}

void TableSetGuild::Draw(void)
{
    if (trans_.modelId >= 0)
    {
        MV1SetScale(trans_.modelId, trans_.scl);
        MV1SetPosition(trans_.modelId, trans_.pos);
        MV1SetRotationXYZ(trans_.modelId, trans_.rot);
        MV1DrawModel(trans_.modelId);
    }
}

void TableSetGuild::Release(void)
{
    isValid_ = false;
}

VECTOR  TableSetGuild::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR  TableSetGuild::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE TableSetGuild::GetHitType() const
{
    return HIT_TYPE::SPHERE;
}

VECTOR TableSetGuild::GetHitPosition(void) const
{
    return trans_.pos;
}

float  TableSetGuild::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool TableSetGuild::IsValid(void) const
{
    return isValid_;
}

void  TableSetGuild::ShowUI(void)
{
}

void TableSetGuild::HideUI(void)
{
}

void TableSetGuild::OnPlayerHit(void)
{
    // フェンスに当たったら特に何もしない（必要ならここに処理）
}

void TableSetGuild::OnPlayerExit(void)
{
    // フェンスから離れたときの処理があればここに
}

Transform& TableSetGuild::GetTransform(void)
{
    return trans_;
}

