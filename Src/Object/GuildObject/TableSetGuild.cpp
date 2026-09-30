#include "TableSetGuild.h"
#include "../../Manager/Generic/ResourceManager.h"

TableSetGuild::TableSetGuild(void)
    : isValid_(false)
{
    radius_ = RADIUS;
}

TableSetGuild::~TableSetGuild(void)
{
    Release();
}

void TableSetGuild::Init(void)
{
    const float POSITION_X = 0.0f;                      // 配置X座標
    const float POSITION_Y = 0.0f;                      // 配置Y座標
    const float POSITION_Z = 0.0f;                      // 配置Z座標
    const float MODEL_SCALE = 0.07f;                    // モデル描画スケール
    const float ROTATION_ZERO = 0.0f;                   // 回転角のゼロ値

    transform_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(
        ResourceManager::SRC::TABLE_SET
    );

    transform_.position = { POSITION_X, POSITION_Y, POSITION_Z };
    transform_.scale = { MODEL_SCALE, MODEL_SCALE, MODEL_SCALE };
    transform_.rotation = { ROTATION_ZERO, ROTATION_ZERO, ROTATION_ZERO };
    radius_ = RADIUS;

    isValid_ = true;
}

void TableSetGuild::Update(void)
{
    hitMin_ = {
        transform_.position.x - WIDTH / 2,
        transform_.position.y - HEIGHT / 2,
        transform_.position.z - DEPTH / 2
    };

    hitMax_ = {
        transform_.position.x + WIDTH / 2,
        transform_.position.y + HEIGHT / 2,
        transform_.position.z + DEPTH / 2
    };
}

void TableSetGuild::Draw(void)
{
    if (transform_.modelId >= 0)
    {
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }
}

void TableSetGuild::Release(void)
{
    isValid_ = false;
}

VECTOR TableSetGuild::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR TableSetGuild::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE TableSetGuild::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR TableSetGuild::GetHitPosition(void) const
{
    return transform_.position;
}

float TableSetGuild::GetHitRadius(void) const
{
    return radius_;
}

bool TableSetGuild::IsValid(void) const
{
    return isValid_;
}

void TableSetGuild::ShowUI(void)
{
}

void TableSetGuild::HideUI(void)
{
}

void TableSetGuild::OnPlayerHit(void)
{
}

void TableSetGuild::OnPlayerExit(void)
{
}

Transform& TableSetGuild::GetTransform(void)
{
    return transform_;
}