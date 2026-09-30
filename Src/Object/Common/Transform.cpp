#include "Transform.h"

#include <DxLib.h>

#include "../../Utility/Utility.h"

Transform::Transform(void)
{
    const int INVALID_MODEL_ID = -1;
    modelId = INVALID_MODEL_ID;

    scale = Utility::VECTOR_ONE;
    rotation = Utility::VECTOR_ZERO;
    position = Utility::VECTOR_ZERO;
    localPosition = Utility::VECTOR_ZERO;

    matrixScale = MGetIdent();
    matrixRotation = MGetIdent();
    matrixPosition = MGetIdent();

    quaternionRotation = Quaternion();
    quaternionRotationLocal = Quaternion();
}

Transform::Transform(int modelHandleId)
{
    modelId = modelHandleId;

    scale = Utility::VECTOR_ONE;
    rotation = Utility::VECTOR_ZERO;
    position = Utility::VECTOR_ZERO;
    localPosition = Utility::VECTOR_ZERO;

    matrixScale = MGetIdent();
    matrixRotation = MGetIdent();
    matrixPosition = MGetIdent();

    quaternionRotation = Quaternion();
    quaternionRotationLocal = Quaternion();
}

Transform::~Transform(void)
{
}

void Transform::Update(void)
{
    matrixScale = MGetScale(scale);

    rotation = quaternionRotation.ToEuler();
    matrixRotation = quaternionRotation.ToMatrix();

    matrixPosition = MGetTranslate(position);

    MATRIX combinedMatrix = MGetIdent();
    Quaternion combinedQuaternion = quaternionRotation.Mult(
        quaternionRotation, quaternionRotationLocal);

    combinedMatrix = MMult(combinedMatrix, combinedQuaternion.ToMatrix());
    combinedMatrix = MMult(combinedMatrix, matrixPosition);

    const int INVALID_MODEL_ID = -1;

    if (modelId != INVALID_MODEL_ID)
    {
        MV1SetMatrix(modelId, combinedMatrix);
    }
}

void Transform::Release(void)
{
}

void Transform::SetModel(int modelHandleId)
{
    modelId = modelHandleId;
}

VECTOR Transform::GetForward(void) const
{
    return GetDirection(Utility::DIRECTION_FORWARD);
}

VECTOR Transform::GetBack(void) const
{
    return GetDirection(Utility::DIRECTION_BACKWARD);
}

VECTOR Transform::GetRight(void) const
{
    return GetDirection(Utility::DIRECTION_RIGHT);
}

VECTOR Transform::GetLeft(void) const
{
    return GetDirection(Utility::DIRECTION_LEFT);
}

VECTOR Transform::GetUp(void) const
{
    return GetDirection(Utility::DIRECTION_UP);
}

VECTOR Transform::GetDown(void) const
{
    return GetDirection(Utility::DIRECTION_DOWN);
}

VECTOR Transform::GetDirection(const VECTOR& targetVector) const
{
    return quaternionRotation.PosAxis(targetVector);
}