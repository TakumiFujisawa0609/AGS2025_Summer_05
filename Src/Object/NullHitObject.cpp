#include "NullHitObject.h"

VECTOR NullHitObject::GetHitPosition(void) const
{
    return { 0,0,0 };
}

float NullHitObject::GetHitRadius(void) const
{
    return 0.0f;
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
