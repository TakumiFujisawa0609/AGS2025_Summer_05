#include "CollisionManager.h"

CollisionManager* CollisionManager::instance_ = nullptr;

//インスタンスの生成
void CollisionManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new CollisionManager();
		instance_->Init();
	}
}

//インスタンスの取得
CollisionManager& CollisionManager::GetInstance(void)
{
	return *instance_;
}

//初期化処理
void CollisionManager::Init(void)
{
	hitObjects_.clear();
}

//登録(ポインタ渡し)
void CollisionManager::Register(HitObject* obj)
{
	hitObjects_.push_back(obj);
}

//全てクリア
void CollisionManager::Clear(void)
{
	hitObjects_.clear();
}

//プレイヤーとの当たり判定チェック(UI表示)
void CollisionManager::CheckHitWithPlayer(const VECTOR playerPos, float PlayerRadus)
{
	for (HitObject* obj : hitObjects_)
	{
		if (Collision::IsHitSpheres(playerPos, PlayerRadus, obj->GetHitPosition(), obj->GetHitRadius()))
		{
			//あったからUIを表示
			obj->ShowUI();
		}
		else
		{
			//当たっていないのでUIを非表示
			obj->HideUI();

		}
	}
}

void CollisionManager::Destroy(void)
{
	delete instance_;
}



