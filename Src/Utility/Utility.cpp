#include "Utility.h"

#include <DxLib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "../Manager/Generic/SceneManager.h"

int Utility::Round(float value)
{
    return static_cast<int>(roundf(value));
}

std::vector<std::string> Utility::Split(std::string& line, char delimiter)
{
    std::istringstream stream(line);
    std::string field;
    std::vector<std::string> result;

    while (getline(stream, field, delimiter))
    {
        result.push_back(field);
    }

    return result;
}

double Utility::RadianToDegreeDouble(double radian)
{
    const double HALF_CIRCLE_DEGREE = 180.0;
    return radian * (HALF_CIRCLE_DEGREE / DX_PI);
}

float Utility::RadianToDegreeFloat(float radian)
{
    const float HALF_CIRCLE_DEGREE = 180.0f;
    return radian * (HALF_CIRCLE_DEGREE / DX_PI_F);
}

int Utility::RadianToDegreeInt(int radian)
{
    const float HALF_CIRCLE_DEGREE = 180.0f;
    return radian * Round(HALF_CIRCLE_DEGREE / DX_PI_F);
}

double Utility::DegreeToRadianDouble(double degree)
{
    const double HALF_CIRCLE_DEGREE = 180.0;
    return degree * (DX_PI / HALF_CIRCLE_DEGREE);
}

float Utility::DegreeToRadianFloat(float degree)
{
    const float HALF_CIRCLE_DEGREE = 180.0f;
    return degree * (DX_PI_F / HALF_CIRCLE_DEGREE);
}

int Utility::DegreeToRadianInt(int degree)
{
    const float HALF_CIRCLE_DEGREE = 180.0f;
    return degree * Round(DX_PI_F / HALF_CIRCLE_DEGREE);
}

double Utility::DegreeIn360(double degree)
{
    const double FULL_CIRCLE_DEGREE = 360.0;
    const double MINIMUM_DEGREE = 0.0;
    
    degree = fmod(degree, FULL_CIRCLE_DEGREE);
    if (degree < MINIMUM_DEGREE)
    {
        degree += FULL_CIRCLE_DEGREE;
    }
    
    return degree;
}

double Utility::RadianIn2PI(double radian)
{
    const double MINIMUM_RADIAN = 0.0;
    
    radian = fmod(radian, DX_TWO_PI);
    if (radian < MINIMUM_RADIAN)
    {
        radian += DX_TWO_PI;
    }

    return radian;
}

int Utility::DirectionNearAroundRadian(float from, float to)
{
    const float CLOCKWISE = 1.0f;
    const float COUNTER_CLOCKWISE = -1.0f;
    const float ZERO_DIFFERENCE = 0.0f;

    float result = CLOCKWISE;
    float difference = to - from;

    if (difference >= ZERO_DIFFERENCE)
    {
        if (difference > DX_PI_F)
        {
            result = COUNTER_CLOCKWISE;
        }
        else
        {
            result = CLOCKWISE;
        }
    }
    else
    {
        if (difference < -DX_PI_F)
        {
            result = CLOCKWISE;
        }
        else
        {
            result = COUNTER_CLOCKWISE;
        }
    }

    return static_cast<int>(result);
}

int Utility::DirectionNearAroundDegree(float from, float to)
{
    const float CLOCKWISE = 1.0f;
    const float COUNTER_CLOCKWISE = -1.0f;
    const float ZERO_DIFFERENCE = 0.0f;
    const float HALF_CIRCLE = 180.0f;
    const float NEGATIVE_HALF_CIRCLE = -180.0f;

    float result = CLOCKWISE;
    float difference = to - from;

    if (difference >= ZERO_DIFFERENCE)
    {
        if (difference > HALF_CIRCLE)
        {
            result = COUNTER_CLOCKWISE;
        }
        else
        {
            result = CLOCKWISE;
        }
    }
    else
    {
        if (difference < NEGATIVE_HALF_CIRCLE)
        {
            result = CLOCKWISE;
        }
        else
        {
            result = COUNTER_CLOCKWISE;
        }
    }
    
    return static_cast<int>(result);
}

int Utility::Lerp(int start, int end, float factor)
{
    const float INTERPOLATION_MAX = 1.0f;
    if (factor >= INTERPOLATION_MAX)
    {
        return end;
    }

    int result = start;
    result += Round(factor * static_cast<float>(end - start));

    return result;
}

float Utility::Lerp(float start, float end, float factor)
{
    const float INTERPOLATION_MAX = 1.0f;
    if (factor >= INTERPOLATION_MAX)
    {
        return end;
    }

    float result = start;
    result += factor * (end - start);

    return result;
}

double Utility::Lerp(double start, double end, double factor)
{
    const double INTERPOLATION_MAX = 1.0;
    if (factor >= INTERPOLATION_MAX)
    {
        return end;
    }

    double result = start;
    result += factor * (end - start);

    return result;
}

Vector2 Utility::Lerp(const Vector2& start, const Vector2& end, float factor)
{
    const float INTERPOLATION_MAX = 1.0f;
    if (factor >= INTERPOLATION_MAX)
    {
        return end;
    }

    Vector2 result = start;
    result.x += Round(factor * static_cast<float>((end.x - start.x)));
    result.y += Round(factor * static_cast<float>((end.y - start.y)));

    return result;
}

VECTOR Utility::Lerp(const VECTOR& start, const VECTOR& end, float factor)
{
    const float INTERPOLATION_MAX = 1.0f;
    if (factor >= INTERPOLATION_MAX)
    {
        return end;
    }

    VECTOR result = start;
    result.x += factor * (end.x - start.x);
    result.y += factor * (end.y - start.y);
    result.z += factor * (end.z - start.z);

    return result;
}

double Utility::LerpDegree(double start, double end, double factor)
{
    double result;
    double difference = end - start;
    
    const double HALF_CIRCLE = 180.0;
    const double NEGATIVE_HALF_CIRCLE = -180.0;
    const double FULL_CIRCLE = 360.0;
    const double MINIMUM_DEGREE = 0.0;

    if (difference < NEGATIVE_HALF_CIRCLE)
    {
        end += FULL_CIRCLE;
        result = Lerp(start, end, factor);
        
        if (result >= FULL_CIRCLE)
        {
            result -= FULL_CIRCLE;
        }
    }
    else if (difference > HALF_CIRCLE)
    {
        end -= FULL_CIRCLE;
        result = Lerp(start, end, factor);

        if (result < MINIMUM_DEGREE)
        {
            result += FULL_CIRCLE;
        }
    }
    else
    {
        result = Lerp(start, end, factor);
    }

    return result;
}

COLOR_F Utility::Lerp(const COLOR_F& start, const COLOR_F& end, float factor)
{
    const float INTERPOLATION_MAX = 1.0f;
    if (factor >= INTERPOLATION_MAX)
    {
        return end;
    }

    COLOR_F result = start;
    result.r += factor * (end.r - start.r);
    result.g += factor * (end.g - start.g);
    result.b += factor * (end.b - start.b);
    result.a += factor * (end.a - start.a);

    return result;
}

Vector2 Utility::Bezier(
    const Vector2& point1, 
    const Vector2& point2, 
    const Vector2& point3, 
    float factor)
{
    Vector2 intermediateA = Lerp(point1, point2, factor);
    Vector2 intermediateB = Lerp(point2, point3, factor);

    return Lerp(intermediateA, intermediateB, factor);
}

VECTOR Utility::Bezier(
    const VECTOR& point1, 
    const VECTOR& point2, 
    const VECTOR& point3, 
    float factor)
{
    VECTOR intermediateA = Lerp(point1, point2, factor);
    VECTOR intermediateB = Lerp(point2, point3, factor);

    return Lerp(intermediateA, intermediateB, factor);
}

VECTOR Utility::RotateXZPosition(
    const VECTOR& centerPosition, 
    const VECTOR& radiusPosition, 
    float radian)
{
    float calculatedX = ((radiusPosition.x - centerPosition.x) * cosf(radian)) - 
                        ((radiusPosition.z - centerPosition.z) * sinf(radian));
                        
    float calculatedZ = ((radiusPosition.x - centerPosition.x) * sinf(radian)) + 
                        ((radiusPosition.z - centerPosition.z) * cosf(radian));

    return VGet(
        centerPosition.x + calculatedX, 
        radiusPosition.y, 
        centerPosition.z + calculatedZ
    );
}

double Utility::Magnitude(const Vector2& vector)
{
    return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

double Utility::Magnitude(const VECTOR& vector)
{
    return sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
}

float Utility::MagnitudeF(const VECTOR& vector)
{
    return sqrtf((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
}

int Utility::SqrMagnitude(const Vector2& vector)
{
    return (vector.x * vector.x) + (vector.y * vector.y);
}

float Utility::SqrMagnitudeF(const VECTOR& vector)
{
    return (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
}

double Utility::SqrMagnitude(const VECTOR& vector)
{
    return (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
}

double Utility::SqrMagnitude(const VECTOR& vector1, const VECTOR& vector2)
{
    const double SQUARE_POWER = 2.0;
    
    double differenceX = pow(vector2.x - vector1.x, SQUARE_POWER);
    double differenceY = pow(vector2.y - vector1.y, SQUARE_POWER);
    double differenceZ = pow(vector2.z - vector1.z, SQUARE_POWER);
    
    return differenceX + differenceY + differenceZ;
}

double Utility::Distance(const Vector2& vector1, const Vector2& vector2)
{
    const double SQUARE_POWER = 2.0;
    
    double differenceX = pow(vector2.x - vector1.x, SQUARE_POWER);
    double differenceY = pow(vector2.y - vector1.y, SQUARE_POWER);
    
    return sqrt(differenceX + differenceY);
}

double Utility::Distance(const VECTOR& vector1, const VECTOR& vector2)
{
    const double SQUARE_POWER = 2.0;
    
    double differenceX = pow(vector2.x - vector1.x, SQUARE_POWER);
    double differenceY = pow(vector2.y - vector1.y, SQUARE_POWER);
    double differenceZ = pow(vector2.z - vector1.z, SQUARE_POWER);
    
    return sqrt(differenceX + differenceY + differenceZ);
}

bool Utility::Equals(const VECTOR& vector1, const VECTOR& vector2)
{
    if (vector1.x == vector2.x && vector1.y == vector2.y && vector1.z == vector2.z)
    {
        return true;
    }

    return false;
}

bool Utility::EqualsVZero(const VECTOR& vector)
{
    const VECTOR& zeroVector = VECTOR_ZERO;
    
    if (vector.x == zeroVector.x && vector.y == zeroVector.y && vector.z == zeroVector.z)
    {
        return true;
    }
    
    return false;
}

VECTOR Utility::Normalize(const Vector2& vector)
{
    const float Z_AXIS_VALUE = 0.0f;
    
    VECTOR result = VGet(
        static_cast<float>(vector.x),
        static_cast<float>(vector.y),
        Z_AXIS_VALUE
    );

    float length = static_cast<float>(Magnitude(vector));

    result.x /= length;
    result.y /= length;
    result.z /= length;

    return result;
}

VECTOR Utility::VNormalize(const VECTOR& vector)
{
    if (Utility::EqualsVZero(vector))
    {
        return vector;
    }
    
    return VNorm(vector);
}

double Utility::AngleDegree(const VECTOR& fromVector, const VECTOR& toVector)
{
    auto fromLength = SqrMagnitude(fromVector);
    auto toLength = SqrMagnitude(toVector);
    auto denominator = sqrt(fromLength * toLength);
    
    const double ZERO_ANGLE = 0.0;
    
    if (denominator < EPSILON_NORMAL_SQRT)
    {
        return ZERO_ANGLE;
    }

    auto dotProduct = VDot(fromVector, toVector) / denominator;

    const float DOT_MIN = -1.0f;
    const float DOT_MAX = 1.0f;

    if (dotProduct < DOT_MIN)
    {
        dotProduct = DOT_MIN;
    }
    
    if (dotProduct > DOT_MAX)
    {
        dotProduct = DOT_MAX;
    }

    const double HALF_CIRCLE_DEGREE = 180.0;
    
    return acos(dotProduct) * (HALF_CIRCLE_DEGREE / DX_PI);
}

void Utility::DrawLineDirection(
    const VECTOR& position, 
    const VECTOR& direction, 
    int color, 
    float length)
{
    auto normalizedDirection = Utility::VNormalize(direction);
    auto startPosition = VAdd(position, VScale(normalizedDirection, -length));
    auto endPosition = VAdd(position, VScale(normalizedDirection, length));

    DrawLine3D(startPosition, endPosition, color);
    
    const float SPHERE_RADIUS = 5.0f;
    const int SPHERE_DIVISIONS = 5;
    
    DrawSphere3D(
        endPosition, 
        SPHERE_RADIUS, 
        SPHERE_DIVISIONS, 
        color, 
        color, 
        true
    );
}

void Utility::DrawLineXYZ(const VECTOR& position, const MATRIX& rotation, float length)
{
    VECTOR direction;

    const int COLOR_RED = 0xff0000;
    const int COLOR_GREEN = 0x00ff00;
    const int COLOR_BLUE = 0x0000ff;

    direction = VTransform(Utility::DIRECTION_RIGHT, rotation);
    DrawLineDirection(position, direction, COLOR_RED, length);

    direction = VTransform(Utility::DIRECTION_UP, rotation);
    DrawLineDirection(position, direction, COLOR_GREEN, length);

    direction = VTransform(Utility::DIRECTION_FORWARD, rotation);
    DrawLineDirection(position, direction, COLOR_BLUE, length);
}

void Utility::DrawLineXYZ(const VECTOR& position, const Quaternion& rotation, float length)
{
    VECTOR direction;

    const int COLOR_RED = 0xff0000;
    const int COLOR_GREEN = 0x00ff00;
    const int COLOR_BLUE = 0x0000ff;

    direction = rotation.GetRight();
    DrawLineDirection(position, direction, COLOR_RED, length);

    direction = rotation.GetUp();
    DrawLineDirection(position, direction, COLOR_GREEN, length);

    direction = rotation.GetForward();
    DrawLineDirection(position, direction, COLOR_BLUE, length);
}

bool Utility::IsTimeOver(float& totalTime, const float& waitTime)
{
    auto deltaTime = SceneManager::GetInstance().GetDeltaTime();
    totalTime += deltaTime;

    if (totalTime >= waitTime)
    {
        return true;
    }

    return false;
}