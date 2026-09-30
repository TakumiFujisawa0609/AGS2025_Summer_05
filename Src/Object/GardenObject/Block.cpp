#include "Block.h"

Block::Block(ResourceManager::SRC modelType, const VECTOR& position, float blockSize, float scale)
{
    position_ = position;

    modelHandle_ = ResourceManager::GetInstance().LoadModelDuplicate(modelType);

    const float HALF_DIVISOR = 2.0f;                    

    if (modelHandle_ != -1)
    {
        MV1SetScale(modelHandle_, VGet(scale, scale, scale));
        MV1SetPosition(modelHandle_, position_);
    }

    float half = blockSize / HALF_DIVISOR;
    halfSize_ = VGet(half, half, half);
}

Block::~Block(void)
{                      

    if (modelHandle_ != -1)
    {
        MV1DeleteModel(modelHandle_);
    }
}

void Block::Update(void)
{
}

void Block::Draw(void)
{

    if (modelHandle_ != -1)
    {
        MV1DrawModel(modelHandle_);
    }
}

HitObject::HIT_TYPE Block::GetHitType(void) const
{
    return HIT_TYPE::AABB;
}

VECTOR Block::GetHitMin(void) const
{
    return VGet(
        position_.x - halfSize_.x,
        position_.y - halfSize_.y,
        position_.z - halfSize_.z
    );
}

VECTOR Block::GetHitMax(void) const
{
    return VGet(
        position_.x + halfSize_.x,
        position_.y + halfSize_.y,
        position_.z + halfSize_.z
    );
}

void Block::ShowUI(void)
{
}

void Block::HideUI(void)
{
}

void Block::OnPlayerHit(void)
{
}

void Block::OnPlayerExit(void)
{
}