#include "CollisionManager.h"

#include <algorithm>

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

    objPos_ = Utility::VECTOR_ZERO;

    objRadius_ = 0.0f;

    objMin_ = Utility::VECTOR_ZERO;

    objMax_ = Utility::VECTOR_ZERO;

    objSizeX_ = 0.0f;
    
    objSizeZ_ = 0.0f;

    diff_ = Utility::VECTOR_ZERO;;

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
void CollisionManager::CheckHitWithPlayer(VECTOR& playerPos, float playerRadius, const VECTOR& playerMin, const VECTOR& playerMax)
{
    for (auto it = hitObjects_.begin(); it != hitObjects_.end(); )
    {
        std::shared_ptr<HitObject> obj = *it;
        if (!obj || !obj->IsValid())
        {
            it = hitObjects_.erase(it);
            continue;
        }

        switch (obj->GetHitType())
        {
        case HitObject::HIT_TYPE::SPHERE:
            CheckHitSphere(obj, playerPos, playerRadius);
            break;

        case HitObject::HIT_TYPE::AABB:
            CheckHitAABB(obj, playerPos, playerMin, playerMax);
            break;
        }

        it++;
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

void CollisionManager::CheckHitSphere(std::shared_ptr<HitObject> obj, VECTOR& playerPos, float playerRadius)
{
    if (Collision::GetInstance().IsHitSpheres(playerPos, playerRadius, obj->GetHitPosition(), obj->GetHitRadius()))
    {
        // 反発処理（既存のまま）
        diff_ = VSub(playerPos, obj->GetHitPosition());
        float lenSq = Utility::SqrMagnitude(diff_);
        float len = sqrtf(lenSq);
        if (len > 0.0001f)
        {
            VECTOR normal = VScale(diff_, 1.0f / len);
            float pushBack = (playerRadius + obj->GetHitRadius()) - len;
            VECTOR pushVec = VScale(normal, pushBack);
            if (pushVec.y > 0) pushVec.y = 0;
            playerPos = VAdd(playerPos, pushVec);
        }

        obj->ShowUI();
    }
    else
    {
        // SHOW/HIDE 判定（UI距離）
        float distance = VSize(VSub(playerPos, obj->GetHitPosition()));
        
        if (distance < SHOW_RADIUS + playerRadius)
        {
            obj->ShowUI();
        }
        else if (distance > HIDE_RADIUS + playerRadius)
        {
            obj->HideUI();
        }
    }

}

void CollisionManager::CheckHitAABB(std::shared_ptr<HitObject> obj, VECTOR& playerPos, const VECTOR& playerMin, const VECTOR& playerMax)
{
    objMin_ = obj->GetHitMin();
    objMax_ = obj->GetHitMax();

    Vector2F playerCenterXZ =
    {
        (playerMin.x + playerMax.x) / 2.0f,
        (playerMin.z + playerMax.z) / 2.0f
    };

    Vector2F objCenterXZ =
    {
        (objMin_.x + objMax_.x) / 2.0f,
        (objMin_.z + objMax_.z) / 2.0f
    };

    float playerSizeX = static_cast<float>(playerMax.x - playerMin.x);
    float playerSizeZ = static_cast<float>(playerMax.z - playerMin.z);
    objSizeX_ = objMax_.x - objMin_.x;
    objSizeZ_ = objMax_.z - objMin_.z;

    float playerRange = std::max<float>(playerSizeX, playerSizeZ);
    float objRange = std::max<float>(objSizeX_, objSizeZ_);

    if (Collision::GetInstance().IsHitBoxes(playerCenterXZ, playerRange, objCenterXZ, objRange))
    {
        //XYの平面での反発処理
        float dx = std::min<float>(playerMax.x, objMax_.x) - std::max<float>(playerMin.x, objMin_.x);
        float dz = std::min<float>(playerMax.z, objMin_.x) - std::max<float>(playerMin.z, objMin_.z);

        float playerCenterX = (playerMax.x, objMax_.x) / 2.0f;
        float objCenterX = (objMin_.x + objMax_.x) / 2.0f;

        float playerCenterZ = (playerMax.z + playerMax.z) / 2.0f;
        float objCenterZ = (objMin_.z + objMax_.z) / 2.0f;

        if (dx < dz)
        {
            float push = (playerCenterX > objCenterX) ? dx : -dx;
            playerPos.x += push;
        }
        else
        {
            float push = (playerCenterZ > objCenterZ) ? dz : -dz;
            playerPos.z += push;
        }

        obj->ShowUI();
    }
    else
    {
        obj->HideUI();
    }


}