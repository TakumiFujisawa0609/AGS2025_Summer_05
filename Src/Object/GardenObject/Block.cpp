#include "Block.h"

Block::Block(ResourceManager::SRC modelType, const VECTOR& pos, float blockSize, float scale)
{
	pos_ = pos;

	modelHandle_ = ResourceManager::GetInstance().LoadModelDuplicate(modelType);

	if (modelHandle_ != -1)
	{
		// モデルのスケールを設定
        MV1SetScale(modelHandle_, VGet(scale, scale, scale));

		MV1SetPosition(modelHandle_, pos_);
	}

	float half = blockSize / 2.0f;
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
	return VGet(pos_.x - halfSize_.x, pos_.y - halfSize_.y, pos_.z - halfSize_.z);
}

VECTOR Block::GetHitMax(void) const
{
	return VGet(pos_.x + halfSize_.x, pos_.y + halfSize_.y, pos_.z + halfSize_.z);
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
