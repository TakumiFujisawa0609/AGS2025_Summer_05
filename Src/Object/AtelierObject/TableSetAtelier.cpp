#include "TableSetAtelier.h"

#include "../../Manager/Generic/ResourceManager.h"

TableSetAtelier::TableSetAtelier(void)
    : isValid_(false)
{
    const float INITIAL_RADIUS = 50.0f;                 // 初期当たり判定半径

    radius_ = INITIAL_RADIUS;
}

TableSetAtelier::~TableSetAtelier(void)
{
    Release();
}

void TableSetAtelier::Init(void)
{
    const float POSITION_X = 200.0f;                    // 配置X座標
    const float POSITION_Y = 0.0f;                      // 配置Y座標
    const float POSITION_Z = -250.0f;                   // 配置Z座標
    const float MODEL_SCALE = 0.07f;                    // モデルの描画スケール
    const float ROTATION_ZERO = 0.0f;                   // 回転角のゼロ値

    transform_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::TABLE_SET);

    transform_.position = { POSITION_X, POSITION_Y, POSITION_Z };
    transform_.scale = { MODEL_SCALE, MODEL_SCALE, MODEL_SCALE };
    transform_.rotation = { ROTATION_ZERO, ROTATION_ZERO, ROTATION_ZERO };
    radius_ = RADIUS;

    isValid_ = true;
}

void TableSetAtelier::Update(void)
{
    const float HALF_DIVISOR = 2.0f;

    hitMin_ = {
        transform_.position.x - WIDTH / HALF_DIVISOR,
        transform_.position.y - HEIGHT / HALF_DIVISOR,
        transform_.position.z - DEPTH / HALF_DIVISOR
    };

    hitMax_ = {
        transform_.position.x + WIDTH / HALF_DIVISOR,
        transform_.position.y + HEIGHT / HALF_DIVISOR,
        transform_.position.z + DEPTH / HALF_DIVISOR
    };
}

void TableSetAtelier::Draw(void)
{
    const int INVALID_MODEL_ID = 0;

    if (transform_.modelId >= INVALID_MODEL_ID)
    {
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }
}

void TableSetAtelier::Release(void)
{
    isValid_ = false;
}

VECTOR TableSetAtelier::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR TableSetAtelier::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE TableSetAtelier::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR TableSetAtelier::GetHitPosition(void) const
{
    return transform_.position;
}

float TableSetAtelier::GetHitRadius(void) const
{
    return radius_;
}

bool TableSetAtelier::IsValid(void) const
{
    return isValid_;
}

void TableSetAtelier::ShowUI(void)
{
}

void TableSetAtelier::HideUI(void)
{
}

void TableSetAtelier::OnPlayerHit(void)
{
}

void TableSetAtelier::OnPlayerExit(void)
{
}

Transform& TableSetAtelier::GetTransform(void)
{
    return transform_;
}