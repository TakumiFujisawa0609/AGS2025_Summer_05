#define NOMINMAX
#include "CollisionManager.h"

#include <algorithm>

#include "../../Manager/System/Collision.h"
#include "../../Utility/Utility.h"
#include "../../Object/GuildObject/BulletinBoard.h"
#include "../PlayerStop.h"

CollisionManager* CollisionManager::instance_ = nullptr;

void CollisionManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new CollisionManager();
        instance_->Init();
    }
}

CollisionManager& CollisionManager::GetInstance(void)
{
    return *instance_;
}

void CollisionManager::Init(void)
{
    hitObjects_.clear();

    objectPosition_ = Utility::VECTOR_ZERO;

    const float INITIAL_RADIUS = 0.0f;
    objectRadius_ = INITIAL_RADIUS;

    objectMinimum_ = Utility::VECTOR_ZERO;

    objectMaximum_ = Utility::VECTOR_ZERO;

    const float INITIAL_SIZE = 0.0f;
    objectSizeX_ = INITIAL_SIZE;
    objectSizeZ_ = INITIAL_SIZE;

    difference_ = Utility::VECTOR_ZERO;
}

void CollisionManager::Register(const std::shared_ptr<HitObject>& object)
{
    if (object != nullptr)
    {
        hitObjects_.push_back(object);
    }
}

void CollisionManager::Clear(void)
{
    hitObjects_.clear();
}

void CollisionManager::CheckHitWithPlayer(
    Player* player,
    VECTOR& playerPosition,
    float playerRadius,
    const VECTOR& playerMin,
    const VECTOR& playerMax)
{
    for (auto iterator = hitObjects_.begin(); iterator != hitObjects_.end(); )
    {
        std::shared_ptr<HitObject> hitObject = *iterator;

        if (hitObject == nullptr || !hitObject->IsValid())
        {
            iterator = hitObjects_.erase(iterator);
            continue;
        }

        switch (hitObject->GetHitType())
        {
        case HitObject::HIT_TYPE::SPHERE:
            CheckHitSphere(hitObject, playerPosition, playerRadius);
            break;

        case HitObject::HIT_TYPE::AABB:
            CheckHitAABB(hitObject, player, playerPosition, playerMin, playerMax);
            break;
        }

        iterator++;
    }
}

void CollisionManager::Destroy(void)
{
    delete instance_;
    instance_ = nullptr;
}

HitObject* CollisionManager::SafeGet(HitObject* object)
{
    if (object == nullptr || !object->IsValid())
    {
        return &nullObject_;
    }

    return object;
}

void CollisionManager::CheckHitSphere(
    std::shared_ptr<HitObject> object,
    VECTOR& playerPosition,
    float playerRadius)
{
    if (Collision::GetInstance().IsHitSpheres(
        playerPosition,
        playerRadius,
        object->GetHitPosition(),
        object->GetHitRadius()))
    {
        object->OnPlayerHit();
        object->OnPlayerHitSphere(playerPosition, playerRadius);
    }
    else
    {
        float distance = VSize(VSub(playerPosition, object->GetHitPosition()));

        if (distance < SHOW_RADIUS + playerRadius)
        {
            object->OnPlayerHit();
            object->OnPlayerHitSphere(playerPosition, playerRadius);
        }
        else if (distance > HIDE_RADIUS + playerRadius)
        {
            object->OnPlayerExit();
        }
    }
}

void CollisionManager::CheckHitAABB(
    std::shared_ptr<HitObject> object,
    Player* player,
    VECTOR& playerPosition,
    const VECTOR& playerMin,
    const VECTOR& playerMax)
{
    objectMinimum_ = object->GetHitMin();
    objectMaximum_ = object->GetHitMax();

    const float CENTER_MULTIPLIER = 0.5f;

    Vector2F playerCenterXZ =
    {
        (playerMin.x + playerMax.x) * CENTER_MULTIPLIER,
        (playerMin.z + playerMax.z) * CENTER_MULTIPLIER
    };

    Vector2F objectCenterXZ =
    {
        (objectMinimum_.x + objectMaximum_.x) * CENTER_MULTIPLIER,
        (objectMinimum_.z + objectMaximum_.z) * CENTER_MULTIPLIER
    };

    float playerSizeX = playerMax.x - playerMin.x;
    float playerSizeZ = playerMax.z - playerMin.z;
    objectSizeX_ = objectMaximum_.x - objectMinimum_.x;
    objectSizeZ_ = objectMaximum_.z - objectMinimum_.z;

    float playerRange = std::max(playerSizeX, playerSizeZ);
    float objectRange = std::max(objectSizeX_, objectSizeZ_);

    bool isHit = Collision::GetInstance().IsHitBoxes(
        playerCenterXZ,
        playerRange,
        objectCenterXZ,
        objectRange
    );

    object->UpdateUIVisibility(isHit);

    if (isHit)
    {
        object->OnPlayerHit();
        object->OnPlayerHitAABB(player, playerPosition, playerMin, playerMax);
    }
}