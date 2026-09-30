#include "NullHitObject.h"

HitObject::HIT_TYPE NullHitObject::GetHitType(void) const
{
    return HIT_TYPE();
}

VECTOR NullHitObject::GetHitPosition(void) const
{
    const float ZERO_VALUE = 0.0f;
    return { ZERO_VALUE, ZERO_VALUE, ZERO_VALUE };
}

float NullHitObject::GetHitRadius(void) const
{
    const float ZERO_RADIUS = 0.0f;
    return ZERO_RADIUS;
}

VECTOR NullHitObject::GetHitMin(void) const
{
    return VECTOR();
}

VECTOR NullHitObject::GetHitMax(void) const
{
    return VECTOR();
}

void NullHitObject::ShowUI(void)
{
}

void NullHitObject::HideUI(void)
{
}

bool NullHitObject::IsValid(void) const
{
    return false;
}

void NullHitObject::OnPlayerHit(void)
{
}

void NullHitObject::OnPlayerExit(void)
{
}