#include "Collision.h"
#include "../../Utility/Utility.h"

Collision* Collision::instance_ = nullptr;

void Collision::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new Collision();
    }
}

Collision& Collision::GetInstance(void)
{
    return *instance_;
}

void Collision::Init(void)
{
}

bool Collision::IsHitBoxes(
    const Vector2F box1,
    const float box1Range,
    const Vector2F box2,
    const float box2Range) const
{
    const float HALF_DIVISOR = 2.0f;

    float box1Front = box1.y - (box1Range / HALF_DIVISOR);
    float box1Bottom = box1.y + (box1Range / HALF_DIVISOR);
    float box1Right = box1.x + (box1Range / HALF_DIVISOR);
    float box1Left = box1.x - (box1Range / HALF_DIVISOR);

    float box2Front = box2.y - (box2Range / HALF_DIVISOR);
    float box2Bottom = box2.y + (box2Range / HALF_DIVISOR);
    float box2Right = box2.x + (box2Range / HALF_DIVISOR);
    float box2Left = box2.x - (box2Range / HALF_DIVISOR);

    if (box1Left < box2Right && box1Right > box2Left &&
        box1Front < box2Bottom && box1Bottom > box2Front)
    {
        return true;
    }

    return false;
}

bool Collision::IsHitSpheres(
    const VECTOR& position1,
    float radius1,
    const VECTOR& position2,
    float radius2)
{
    bool isHit = false;
    float totalRadius = radius1 + radius2;
    VECTOR positionDifference = VSub(position2, position1);

    // 三平方の定理で比較
    float squaredDistance = (positionDifference.x * positionDifference.x) +
        (positionDifference.y * positionDifference.y) +
        (positionDifference.z * positionDifference.z);

    if (squaredDistance < (totalRadius * totalRadius))
    {
        isHit = true;
    }

    return isHit;
}

bool Collision::IsHitSphereCapsule(
    const VECTOR& spherePosition,
    float sphereRadius,
    const VECTOR& capsulePosition1,
    const VECTOR& capsulePosition2,
    float capsuleRadius)
{
    bool isHit = false;

    VECTOR capsuleVector = VSub(capsulePosition2, capsulePosition1);
    VECTOR capsuleNormalVector = VNorm(capsuleVector);
    VECTOR capsuleToSphereVector = VSub(spherePosition, capsulePosition1);

    float dotProduct = VDot(capsuleNormalVector, capsuleToSphereVector);
    float capsuleLength = Utility::MagnitudeF(capsuleVector);
    float positionRate = dotProduct / capsuleLength;

    VECTOR centerPosition;

    const float RATE_MIN = 0.0f;
    const float RATE_MAX = 1.0f;

    // 球体の位置が３エリアに分割されたカプセル形状のどこにいるか判別
    if (positionRate > RATE_MIN && positionRate <= RATE_MAX)
    {
        centerPosition = VAdd(
            capsulePosition1,
            VScale(capsuleNormalVector, dotProduct)
        );
    }
    else if (positionRate > RATE_MAX)
    {
        centerPosition = capsulePosition2;
    }
    else if (positionRate < RATE_MIN)
    {
        centerPosition = capsulePosition1;
    }

    // 求めた中心点と球体同士の当たり判定
    if (IsHitSpheres(centerPosition, capsuleRadius, spherePosition, sphereRadius))
    {
        isHit = true;
    }
    else
    {
        isHit = false;
    }

    return isHit;
}