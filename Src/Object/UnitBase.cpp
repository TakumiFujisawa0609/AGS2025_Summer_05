#include "UnitBase.h"

#include "../Application.h"
#include "../Utility/Utility.h"

UnitBase::UnitBase(void)
{
    const int INVALID_MODEL_ID = -1;
    const float INITIAL_VALUE = 0.0f;

    transform_.modelId = INVALID_MODEL_ID;
    transform_.position = { INITIAL_VALUE, INITIAL_VALUE, INITIAL_VALUE };
    transform_.scale = { INITIAL_VALUE, INITIAL_VALUE, INITIAL_VALUE };
    transform_.rotation = { INITIAL_VALUE, INITIAL_VALUE, INITIAL_VALUE };

    radius_ = INITIAL_VALUE;
    speed_ = INITIAL_VALUE;
    movementVector_ = Utility::VECTOR_ZERO;
}

UnitBase::~UnitBase(void)
{
}

void UnitBase::Turn(const float degree, const VECTOR& axis)
{
    transform_.quaternionRotation = transform_.quaternionRotation.Mult(
        transform_.quaternionRotation,
        Quaternion::AngleAxis(Utility::DegreeToRadianFloat(degree), axis)
    );
}

void UnitBase::InitAnimation(void)
{
}