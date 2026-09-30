#define NOMINMAX
#include "HitObject.h"

#include <cmath>
#include <algorithm>
#include "../../Application.h"
#include "../Player.h"

HitObject::HitObject(void)
{
    const int INVALID_STAGE_ID = -1;
    const int INITIAL_DELAY_FRAMES = 0;

    stageId_ = INVALID_STAGE_ID;
    uiVisible_ = false;
    uiHideDelayFrames_ = INITIAL_DELAY_FRAMES;
}

VECTOR HitObject::GetHitPosition(void) const
{
    const float ZERO_COORDINATE = 0.0f;
    return VGet(ZERO_COORDINATE, ZERO_COORDINATE, ZERO_COORDINATE);
}

float HitObject::GetHitRadius(void) const
{
    const float ZERO_RADIUS = 0.0f;
    return ZERO_RADIUS;
}

VECTOR HitObject::GetHitMin(void) const
{
    const float ZERO_COORDINATE = 0.0f;
    return VGet(ZERO_COORDINATE, ZERO_COORDINATE, ZERO_COORDINATE);
}

VECTOR HitObject::GetHitMax(void) const
{
    const float ZERO_COORDINATE = 0.0f;
    return VGet(ZERO_COORDINATE, ZERO_COORDINATE, ZERO_COORDINATE);
}

bool HitObject::IsValid(void) const
{
    return true;
}

void HitObject::OnPlayerHitSphere(VECTOR& playerPosition, float playerRadius)
{
    VECTOR vectorToPlayer = VSub(playerPosition, GetHitPosition());

    float squaredDistance = VDot(vectorToPlayer, vectorToPlayer);
    float sumOfRadii = playerRadius + GetHitRadius();
    float squaredSumOfRadii = sumOfRadii * sumOfRadii;

    const float EPSILON = 0.0001f;

    if (squaredDistance < squaredSumOfRadii && squaredDistance > EPSILON)
    {
        float distance = sqrtf(squaredDistance);

        const float NUMERATOR = 1.0f;
        VECTOR normalVector = VScale(vectorToPlayer, NUMERATOR / distance);

        float pushBackDistance = sumOfRadii - distance;

        const float PUSH_MULTIPLIER = 1.5f;
        VECTOR pushBackVector = VScale(normalVector, pushBackDistance * PUSH_MULTIPLIER);

        const float UPWARD_LIMIT = 0.0f;

        if (pushBackVector.y > UPWARD_LIMIT)
        {
            pushBackVector.y = UPWARD_LIMIT;
        }

        playerPosition = VAdd(playerPosition, pushBackVector);
    }
}

void HitObject::UpdateUIVisibility(bool isHit)
{
    if (isHit)
    {
        uiVisible_ = true;
        uiHideDelayFrames_ = MAXIMUM_UI_HIDE_DELAY_FRAMES;
        ShowUI();
    }
    else
    {
        const int ZERO_FRAMES = 0;

        if (uiHideDelayFrames_ > ZERO_FRAMES)
        {
            uiHideDelayFrames_--;
            ShowUI();
        }
        else if (uiVisible_)
        {
            uiVisible_ = false;
            HideUI();
            OnPlayerExit();
        }
    }
}

void HitObject::OnPlayerHitAABB(
    Player* player,
    VECTOR& playerPosition,
    const VECTOR& playerMinimum,
    const VECTOR& playerMaximum)
{
    VECTOR objectMinimum = GetHitMin();
    VECTOR objectMaximum = GetHitMax();

    float overlapX = std::min(playerMaximum.x, objectMaximum.x) -
        std::max(playerMinimum.x, objectMinimum.x);

    float overlapZ = std::min(playerMaximum.z, objectMaximum.z) -
        std::max(playerMinimum.z, objectMinimum.z);

    const float ZERO_OVERLAP = 0.0f;

    if (overlapX > ZERO_OVERLAP && overlapZ > ZERO_OVERLAP)
    {
        const float HALF_MULTIPLIER = 0.5f;

        float playerCenterX = (playerMinimum.x + playerMaximum.x) * HALF_MULTIPLIER;
        float objectCenterX = (objectMinimum.x + objectMaximum.x) * HALF_MULTIPLIER;
        float playerCenterZ = (playerMinimum.z + playerMaximum.z) * HALF_MULTIPLIER;
        float objectCenterZ = (objectMinimum.z + objectMaximum.z) * HALF_MULTIPLIER;

        const int BLOCK_DIRECTION_POSITIVE = 1;
        const int BLOCK_DIRECTION_NEGATIVE = -1;
        const float ZERO_PUSH = 0.0f;

        if (overlapX < overlapZ)
        {
            float pushAmount = (playerCenterX > objectCenterX) ? overlapX : -overlapX;
            playerPosition.x += pushAmount;

            if (player != nullptr)
            {
                player->SetBlockedDirectionX(
                    (pushAmount > ZERO_PUSH) ?
                    BLOCK_DIRECTION_NEGATIVE : BLOCK_DIRECTION_POSITIVE
                );
            }
        }
        else
        {
            float pushAmount = (playerCenterZ > objectCenterZ) ? overlapZ : -overlapZ;
            playerPosition.z += pushAmount;

            if (player != nullptr)
            {
                player->SetBlockedDirectionZ(
                    (pushAmount > ZERO_PUSH) ?
                    BLOCK_DIRECTION_NEGATIVE : BLOCK_DIRECTION_POSITIVE
                );
            }
        }
    }
}