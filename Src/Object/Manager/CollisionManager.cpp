#include "CollisionManager.h"

#include "../../Manager/System/Collision.h"
#include "../../Utility/Utility.h"
#include "../../Object/GuildObject/BulletinBoard.h"

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
void CollisionManager::Register(const std::shared_ptr<HitObject>& obj)
{
    if (obj) hitObjects_.push_back(obj);
}

//全てクリア
void CollisionManager::Clear(void)
{
    hitObjects_.clear();
}

//プレイヤーとの当たり判定チェック(UI表示)
void CollisionManager::CheckHitWithPlayer(VECTOR& playerPos, float playerRadius)
{
    for (auto it = hitObjects_.begin(); it != hitObjects_.end(); )
    {
        std::shared_ptr<HitObject> obj = *it;
        if (!obj || !obj->IsValid())
        {
            it = hitObjects_.erase(it);
            continue;
        }

        VECTOR objPos = obj->GetHitPosition();
        float objRadius = obj->GetHitRadius();

        VECTOR diff = VSub(playerPos, objPos);
        float lenSq = Utility::SqrMagnitude(diff);
        float radiusSum = playerRadius + objRadius;

        // プッシュバック処理は同じ
        if (lenSq < radiusSum * radiusSum)
        {
            float len = sqrtf(lenSq);
            if (len > 0.0001f)
            {
                VECTOR normal = VScale(diff, 1.0f / len);
                float pushBack = radiusSum - len;
                VECTOR pushVec = VScale(normal, pushBack);

                if (pushVec.y > 0)
                {
                    pushVec.y = 0;
                }
                playerPos = VAdd(playerPos, pushVec);
            }
        }

        // UI表示判定は別の距離で行う
        float distance = sqrtf(lenSq);
        if (distance < SHOW_RADIUS + playerRadius)
        {
            obj->ShowUI();
        }
        else if (distance > HIDE_RADIUS + playerRadius)
        {
            obj->HideUI();
        }
        // SHOW_RADIUS と HIDE_RADIUS の間では状態を維持

        ++it;
    }
}

//リソースの解放処理
void CollisionManager::Destroy(void)
{
    delete instance_;
    instance_ = nullptr;
}

HitObject* CollisionManager::SafeGet(HitObject* obj)
{
    if (obj == nullptr || !obj->IsValid())
        return &nullObject_;
    return obj;
}