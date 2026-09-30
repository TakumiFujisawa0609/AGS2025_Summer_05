#include "Quaternion.h"
#include <math.h>
#include <DxLib.h>
#include "../Utility/Utility.h"

Quaternion::Quaternion(void)
{
    w = 1.0;
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Quaternion::Quaternion(const VECTOR& radian)
{
    Quaternion quaternion = Euler(radian.x, radian.y, radian.z);
    w = quaternion.w;
    x = quaternion.x;
    y = quaternion.y;
    z = quaternion.z;
}

Quaternion::Quaternion(double scalar, double vectorX, double vectorY, double vectorZ)
{
    w = scalar;
    x = vectorX;
    y = vectorY;
    z = vectorZ;
}

Quaternion::~Quaternion(void)
{
}

Quaternion Quaternion::Euler(const VECTOR& radian)
{
    return Euler(radian.x, radian.y, radian.z);
}

Quaternion Quaternion::Euler(double radianX, double radianY, double radianZ)
{
    Quaternion result = Quaternion();

    radianX = Utility::RadianIn2PI(radianX);
    radianY = Utility::RadianIn2PI(radianY);
    radianZ = Utility::RadianIn2PI(radianZ);

    double cosineZ = cos(radianZ / 2.0);
    double sineZ = sin(radianZ / 2.0);
    double cosineX = cos(radianX / 2.0);
    double sineX = sin(radianX / 2.0);
    double cosineY = cos(radianY / 2.0);
    double sineY = sin(radianY / 2.0);

    result.w = cosineX * cosineY * cosineZ + sineX * sineY * sineZ;
    result.x = sineX * cosineY * cosineZ + cosineX * sineY * sineZ;
    result.y = cosineX * sineY * cosineZ - sineX * cosineY * sineZ;
    result.z = cosineX * cosineY * sineZ - sineX * sineY * cosineZ;

    return result;
}

Quaternion Quaternion::Mult(const Quaternion& quaternion1, const Quaternion& quaternion2)
{
    Quaternion result = Quaternion();

    double dot11 = quaternion1.w * quaternion2.w;
    double dot12 = -quaternion1.x * quaternion2.x;
    double dot13 = -quaternion1.y * quaternion2.y;
    double dot14 = -quaternion1.z * quaternion2.z;
    result.w = dot11 + dot12 + dot13 + dot14;

    double dot21 = quaternion1.w * quaternion2.x;
    double dot22 = quaternion2.w * quaternion1.x;
    double dot23 = quaternion1.y * quaternion2.z;
    double dot24 = -quaternion1.z * quaternion2.y;
    result.x = dot21 + dot22 + dot23 + dot24;

    double dot31 = quaternion1.w * quaternion2.y;
    double dot32 = quaternion2.w * quaternion1.y;
    double dot33 = quaternion1.z * quaternion2.x;
    double dot34 = -quaternion1.x * quaternion2.z;
    result.y = dot31 + dot32 + dot33 + dot34;

    double dot41 = quaternion1.w * quaternion2.z;
    double dot42 = quaternion2.w * quaternion1.z;
    double dot43 = quaternion1.x * quaternion2.y;
    double dot44 = -quaternion1.y * quaternion2.x;
    result.z = dot41 + dot42 + dot43 + dot44;

    return result;
}

Quaternion Quaternion::Mult(const Quaternion& quaternion) const
{
    return Mult(Quaternion(w, x, y, z), quaternion);
}

Quaternion Quaternion::AngleAxis(double radian, VECTOR axis)
{
    Quaternion result = Quaternion();

    result.w = 1.0;
    result.x = 0.0;
    result.y = 0.0;
    result.z = 0.0;

    double squaredNorm = static_cast<double>(axis.x) * static_cast<double>(axis.x) +
        static_cast<double>(axis.y) * static_cast<double>(axis.y) +
        static_cast<double>(axis.z) * static_cast<double>(axis.z);

    if (squaredNorm <= 0.0)
    {
        return result;
    }

    double inverseNorm = 1.0 / sqrt(squaredNorm);
    axis.x = static_cast<float>(axis.x * inverseNorm);
    axis.y = static_cast<float>(axis.y * inverseNorm);
    axis.z = static_cast<float>(axis.z * inverseNorm);

    double cosineHalfRadian = cos(0.5 * radian);
    double sineHalfRadian = sin(0.5 * radian);

    result.w = cosineHalfRadian;
    result.x = sineHalfRadian * axis.x;
    result.y = sineHalfRadian * axis.y;
    result.z = sineHalfRadian * axis.z;

    return result;
}

VECTOR Quaternion::PosAxis(const Quaternion& quaternion, VECTOR axis)
{
    Quaternion temporaryQuaternion = Quaternion();
    temporaryQuaternion = temporaryQuaternion.Mult(quaternion);
    temporaryQuaternion = temporaryQuaternion.Mult(Quaternion(0.0, axis.x, axis.y, axis.z));
    temporaryQuaternion = temporaryQuaternion.Mult(quaternion.Inverse());

    return { static_cast<float>(temporaryQuaternion.x), static_cast<float>(temporaryQuaternion.y), static_cast<float>(temporaryQuaternion.z) };
}

VECTOR Quaternion::PosAxis(VECTOR position) const
{
    return PosAxis(Quaternion(w, x, y, z), position);
}

VECTOR Quaternion::ToEuler(const Quaternion& quaternion)
{
    VECTOR result;

    double element11 = 2.0 * (quaternion.x * quaternion.z + quaternion.w * quaternion.y);
    double element12 = quaternion.w * quaternion.w - quaternion.x * quaternion.x - quaternion.y * quaternion.y + quaternion.z * quaternion.z;
    double element21 = -2.0 * (quaternion.y * quaternion.z - quaternion.w * quaternion.x);
    double element31 = 2.0 * (quaternion.x * quaternion.y + quaternion.w * quaternion.z);
    double element32 = quaternion.w * quaternion.w - quaternion.x * quaternion.x + quaternion.y * quaternion.y - quaternion.z * quaternion.z;

    result.x = static_cast<float>(asin(element21));
    result.y = static_cast<float>(atan2(element11, element12));
    result.z = static_cast<float>(atan2(element31, element32));

    return result;
}

VECTOR Quaternion::ToEuler(void) const
{
    return ToEuler(Quaternion(w, x, y, z));
}

MATRIX Quaternion::ToMatrix(const Quaternion& quaternion)
{
    MATRIX matrix;

    float quaternionX = static_cast<float>(quaternion.x);
    float quaternionY = static_cast<float>(quaternion.y);
    float quaternionZ = static_cast<float>(quaternion.z);
    float quaternionW = static_cast<float>(quaternion.w);

    float squaredX = quaternionX * quaternionX * 2.0f;
    float squaredY = quaternionY * quaternionY * 2.0f;
    float squaredZ = quaternionZ * quaternionZ * 2.0f;
    float crossYZ = quaternionY * quaternionZ * 2.0f;
    float crossXZ = quaternionX * quaternionZ * 2.0f;
    float crossXY = quaternionX * quaternionY * 2.0f;
    float crossWX = quaternionW * quaternionX * 2.0f;
    float crossWY = quaternionW * quaternionY * 2.0f;
    float crossWZ = quaternionW * quaternionZ * 2.0f;

    matrix.m[0][0] = 1.0f - (squaredY + squaredZ);
    matrix.m[0][1] = crossXY + crossWZ;
    matrix.m[0][2] = crossXZ - crossWY;
    matrix.m[0][3] = 0.0f;

    matrix.m[1][0] = crossXY - crossWZ;
    matrix.m[1][1] = 1.0f - (squaredX + squaredZ);
    matrix.m[1][2] = crossYZ + crossWX;
    matrix.m[1][3] = 0.0f;

    matrix.m[2][0] = crossXZ + crossWY;
    matrix.m[2][1] = crossYZ - crossWX;
    matrix.m[2][2] = 1.0f - (squaredX + squaredY);
    matrix.m[2][3] = 0.0f;

    matrix.m[3][0] = 0.0f;
    matrix.m[3][1] = 0.0f;
    matrix.m[3][2] = 0.0f;
    matrix.m[3][3] = 1.0f;

    return matrix;
}

MATRIX Quaternion::ToMatrix(void) const
{
    return ToMatrix(Quaternion(w, x, y, z));
}

Quaternion Quaternion::LookRotation(VECTOR direction)
{
    VECTOR upVector = { 0.0f, 1.0f, 0.0f };
    return LookRotation(direction, upVector);
}

Quaternion Quaternion::LookRotation(VECTOR direction, VECTOR up)
{
    direction = Utility::VNormalize(direction);
    VECTOR rightVector = Utility::VNormalize(VCross(up, direction));
    up = VCross(direction, rightVector);

    float element00 = rightVector.x;
    float element01 = rightVector.y;
    float element02 = rightVector.z;
    float element10 = up.x;
    float element11 = up.y;
    float element12 = up.z;
    float element20 = direction.x;
    float element21 = direction.y;
    float element22 = direction.z;

    float traceSum = (element00 + element11) + element22;
    Quaternion resultQuaternion = Quaternion();

    if (traceSum > 0.0f)
    {
        double traceRoot = sqrt(traceSum + 1.0);
        resultQuaternion.w = traceRoot * 0.5;
        traceRoot = 0.5 / traceRoot;
        resultQuaternion.x = (static_cast<double>(element12) - element21) * traceRoot;
        resultQuaternion.y = (static_cast<double>(element20) - element02) * traceRoot;
        resultQuaternion.z = (static_cast<double>(element01) - element10) * traceRoot;
        return resultQuaternion.Normalized();
    }
    if ((element00 >= element11) && (element00 >= element22))
    {
        double traceRoot = sqrt(((1.0f + element00) - element11) - element22);
        double inverseTraceRoot = 0.5 / traceRoot;
        resultQuaternion.x = 0.5 * traceRoot;
        resultQuaternion.y = (static_cast<double>(element01) + element10) * inverseTraceRoot;
        resultQuaternion.z = (static_cast<double>(element02) + element20) * inverseTraceRoot;
        resultQuaternion.w = (static_cast<double>(element12) - element21) * inverseTraceRoot;
        return resultQuaternion.Normalized();
    }
    if (element11 > element22)
    {
        double traceRoot = sqrt(((1.0f + element11) - element00) - element22);
        double inverseTraceRoot = 0.5 / traceRoot;
        resultQuaternion.x = (static_cast<double>(element10) + element01) * inverseTraceRoot;
        resultQuaternion.y = 0.5 * traceRoot;
        resultQuaternion.z = (static_cast<double>(element21) + element12) * inverseTraceRoot;
        resultQuaternion.w = (static_cast<double>(element20) - element02) * inverseTraceRoot;
        return resultQuaternion.Normalized();
    }

    double traceRoot = sqrt(((1.0f + element22) - element00) - element11);
    double inverseTraceRoot = 0.5 / traceRoot;
    resultQuaternion.x = (static_cast<double>(element20) + element02) * inverseTraceRoot;
    resultQuaternion.y = (static_cast<double>(element21) + element12) * inverseTraceRoot;
    resultQuaternion.z = 0.5 * traceRoot;
    resultQuaternion.w = (static_cast<double>(element01) - element10) * inverseTraceRoot;
    return resultQuaternion.Normalized();
}

Quaternion Quaternion::GetRotation(MATRIX matrix)
{
    Quaternion result;

    float traceScalar;
    float traceValue = matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2] + 1.0f;

    if (traceValue >= 1.0f)
    {
        traceScalar = 0.5f / sqrtf(traceValue);
        result.w = 0.25f / traceScalar;
        result.x = (matrix.m[1][2] - matrix.m[2][1]) * traceScalar;
        result.y = (matrix.m[2][0] - matrix.m[0][2]) * traceScalar;
        result.z = (matrix.m[0][1] - matrix.m[1][0]) * traceScalar;
    }
    else
    {
        float maxDiagonal;
        maxDiagonal = matrix.m[1][1] > matrix.m[2][2] ? matrix.m[1][1] : matrix.m[2][2];

        if (maxDiagonal < matrix.m[0][0])
        {
            traceScalar = sqrtf(matrix.m[0][0] - (matrix.m[1][1] + matrix.m[2][2]) + 1.0f);

            float temporaryX = traceScalar * 0.5f;
            traceScalar = 0.5f / traceScalar;
            result.x = temporaryX;
            result.y = (matrix.m[0][1] + matrix.m[1][0]) * traceScalar;
            result.z = (matrix.m[2][0] + matrix.m[0][2]) * traceScalar;
            result.w = (matrix.m[1][2] - matrix.m[2][1]) * traceScalar;
        }
        else if (maxDiagonal == matrix.m[1][1])
        {
            traceScalar = sqrtf(matrix.m[1][1] - (matrix.m[2][2] + matrix.m[0][0]) + 1.0f);

            float temporaryY = traceScalar * 0.5f;
            traceScalar = 0.5f / traceScalar;
            result.x = (matrix.m[0][1] + matrix.m[1][0]) * traceScalar;
            result.y = temporaryY;
            result.z = (matrix.m[1][2] + matrix.m[2][1]) * traceScalar;
            result.w = (matrix.m[2][0] - matrix.m[0][2]) * traceScalar;
        }
        else
        {
            traceScalar = sqrtf(matrix.m[2][2] - (matrix.m[0][0] + matrix.m[1][1]) + 1.0f);

            float temporaryZ = traceScalar * 0.5f;
            traceScalar = 0.5f / traceScalar;
            result.x = (matrix.m[2][0] + matrix.m[0][2]) * traceScalar;
            result.y = (matrix.m[1][2] + matrix.m[2][1]) * traceScalar;
            result.z = temporaryZ;
            result.w = (matrix.m[0][1] - matrix.m[1][0]) * traceScalar;
        }
    }

    return result;
}

VECTOR Quaternion::GetDir(VECTOR direction) const
{
    return PosAxis(direction);
}

VECTOR Quaternion::GetForward(void) const
{
    return GetDir(Utility::DIRECTION_FORWARD);
}

VECTOR Quaternion::GetBack(void) const
{
    return GetDir(Utility::DIRECTION_BACKWARD);
}

VECTOR Quaternion::GetRight(void) const
{
    return GetDir(Utility::DIRECTION_RIGHT);
}

VECTOR Quaternion::GetLeft(void) const
{
    return GetDir(Utility::DIRECTION_LEFT);
}

VECTOR Quaternion::GetUp(void) const
{
    return GetDir(Utility::DIRECTION_UP);
}

VECTOR Quaternion::GetDown(void) const
{
    return GetDir(Utility::DIRECTION_DOWN);
}

double Quaternion::Dot(const Quaternion& quaternion1, const Quaternion& quaternion2)
{
    return (quaternion1.w * quaternion2.w + quaternion1.x * quaternion2.x + quaternion1.y * quaternion2.y + quaternion1.z * quaternion2.z);
}

double Quaternion::Dot(const Quaternion& quaternion) const
{
    return (w * quaternion.w + x * quaternion.x + y * quaternion.y + z * quaternion.z);
}

Quaternion Quaternion::Normalize(const Quaternion& quaternion)
{
    float inverseScale = 1.0f / static_cast<float>(quaternion.Length());
    VECTOR scaledVector = VScale(quaternion.xyz(), inverseScale);
    Quaternion result = Quaternion(quaternion.w * inverseScale, scaledVector.x, scaledVector.y, scaledVector.z);
    return result;
}

Quaternion Quaternion::Normalized(void) const
{
    double magnitude = sqrt(w * w + x * x + y * y + z * z);
    return Quaternion(w / magnitude, x / magnitude, y / magnitude, z / magnitude);
}

void Quaternion::Normalize(void)
{
    double magnitude = sqrt(w * w + x * x + y * y + z * z);

    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

Quaternion Quaternion::Inverse(void) const
{
    double inverseNorm = 1.0 / (w * w + x * x + y * y + z * z);
    Quaternion conjugate = Quaternion(w, -x, -y, -z);
    return Quaternion(conjugate.w * inverseNorm, conjugate.x * inverseNorm, conjugate.y * inverseNorm, conjugate.z * inverseNorm);
}

Quaternion Quaternion::Slerp(Quaternion from, Quaternion to, double ratio)
{
    if (ratio > 1.0)
    {
        ratio = 1.0;
    }
    if (ratio < 0.0)
    {
        ratio = 0.0;
    }

    return SlerpUnclamped(from, to, static_cast<float>(ratio));
}

inline float SIGN(float value)
{
    return (value >= 0.0f) ? +1.0f : -1.0f;
}

inline float NORM(float valueA, float valueB, float valueC, float valueD)
{
    return sqrt(valueA * valueA + valueB * valueB + valueC * valueC + valueD * valueD);
}

Quaternion Quaternion::FromToRotation(VECTOR fromDirection, VECTOR toDirection)
{
    VECTOR rotationAxis = VCross(fromDirection, toDirection);
    double angleDegree = Utility::AngleDegree(fromDirection, toDirection);

    if (angleDegree >= 179.9196)
    {
        VECTOR rightDirection = VCross(fromDirection, Utility::DIRECTION_RIGHT);
        rotationAxis = VCross(rightDirection, fromDirection);
        float axisLengthSquared = rotationAxis.x * rotationAxis.x + rotationAxis.y * rotationAxis.y + rotationAxis.z * rotationAxis.z;
        if (axisLengthSquared < 0.000001f)
        {
            rotationAxis = Utility::DIRECTION_UP;
        }
    }

    rotationAxis = Utility::VNormalize(rotationAxis);
    return Quaternion::AngleAxis(Utility::DegreeToRadianDouble(angleDegree), rotationAxis);
}

Quaternion Quaternion::RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta)
{
    double angleDifference = Quaternion::Angle(from, to);
    if (angleDifference == 0.0)
    {
        return to;
    }

    float ratio = min(1.0f, maxDegreesDelta / static_cast<float>(angleDifference));
    return Quaternion::SlerpUnclamped(from, to, ratio);
}

double Quaternion::Angle(const Quaternion& quaternion1, const Quaternion& quaternion2)
{
    double dotProduct = Quaternion::Dot(quaternion1, quaternion2);
    double arcCosine = acos(dotProduct);
    return arcCosine * (180.0 / DX_PI);
}

Quaternion Quaternion::SlerpUnclamped(Quaternion from, Quaternion to, float ratio)
{
    if (from.LengthSquared() == 0.0)
    {
        if (to.LengthSquared() == 0.0)
        {
            return Identity();
        }
        return to;
    }
    else if (to.LengthSquared() == 0.0)
    {
        return from;
    }

    float cosineHalfAngle = static_cast<float>(from.w * to.w) + VDot(from.xyz(), to.xyz());

    if (cosineHalfAngle >= 1.0f || cosineHalfAngle <= -1.0f)
    {
        return from;
    }
    else if (cosineHalfAngle < 0.0f)
    {
        to.x = to.x * -1.0f;
        to.y = to.y * -1.0f;
        to.z = to.z * -1.0f;
        to.w = -to.w;
        cosineHalfAngle = -cosineHalfAngle;
    }

    float blendFrom;
    float blendTo;
    if (cosineHalfAngle < 0.99f)
    {
        float halfAngle = acosf(cosineHalfAngle);
        float sineHalfAngle = sinf(halfAngle);
        float inverseSineHalfAngle = 1.0f / sineHalfAngle;
        blendFrom = sinf(halfAngle * (1.0f - ratio)) * inverseSineHalfAngle;
        blendTo = sinf(halfAngle * ratio) * inverseSineHalfAngle;
    }
    else
    {
        blendFrom = 1.0f - ratio;
        blendTo = ratio;
    }

    VECTOR blendedVector = VAdd(VScale(from.xyz(), blendFrom), VScale(to.xyz(), blendTo));
    Quaternion result = Quaternion(blendFrom * from.w + blendTo * to.w, blendedVector.x, blendedVector.y, blendedVector.z);

    if (result.LengthSquared() > 0.0)
    {
        return Normalize(result);
    }
    else
    {
        return Identity();
    }
}

Quaternion Quaternion::Identity(void)
{
    return Quaternion(1.0, 0.0, 0.0, 0.0);
}

double Quaternion::Length(void) const
{
    return sqrt(x * x + y * y + z * z + w * w);
}

double Quaternion::LengthSquared(void) const
{
    return x * x + y * y + z * z + w * w;
}

VECTOR Quaternion::xyz(void) const
{
    return { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
}

void Quaternion::ToAngleAxis(float* angle, VECTOR* axis)
{
    if (abs(this->w) > 1.0)
    {
        this->Normalize();
    }

    *angle = 2.0f * acosf(static_cast<float>(this->w));

    if (x == 0.0 && y == 0.0 && z == 0.0)
    {
        *angle = 0.0f;
    }

    float denominator = sqrtf(1.0f - static_cast<float>(this->w * this->w));
    if (denominator > 0.0001f)
    {
        auto vectorXYZ = this->xyz();
        axis->x = vectorXYZ.x / denominator;
        axis->y = vectorXYZ.y / denominator;
        axis->z = vectorXYZ.z / denominator;
    }
    else
    {
        *axis = { 1.0f, 0.0f, 0.0f };
    }
}

Quaternion Quaternion::operator*(float& rhs)
{
    return Quaternion(w * rhs, x * rhs, y * rhs, z * rhs);
}

const Quaternion Quaternion::operator*(const float& rhs)
{
    return Quaternion(w * rhs, x * rhs, y * rhs, z * rhs);
}

Quaternion Quaternion::operator+(Quaternion& rhs)
{
    return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}

const Quaternion Quaternion::operator+(const Quaternion& rhs)
{
    return Quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
}