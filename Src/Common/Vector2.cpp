#include "Vector2.h"

Vector2::Vector2(void)
{
    x = 0;
    y = 0;
}

Vector2::Vector2(int positionX, int positionY)
{
    x = positionX;
    y = positionY;
}

Vector2::~Vector2(void)
{
}

Vector2 Vector2::operator+(const Vector2 value) const
{
    return Vector2(x + value.x, y + value.y);
}

void Vector2::operator+=(const Vector2 value)
{
    // x = value.x; ÇÕë„ì¸Ç…Ç»Ç¡ÇƒÇ¢ÇΩÇΩÇﬂâ¡éZÇ…èCê≥
    x += value.x;
    y += value.y;
}

Vector2 Vector2::operator-(const Vector2 value) const
{
    return Vector2(x - value.x, y - value.y);
}

void Vector2::operator-=(const Vector2 value)
{
    // x = y - value.x; ÇÃÇÊÇ§Ç»åÎãLÇ™Ç†Ç¡ÇΩÇΩÇﬂèCê≥
    x -= value.x;
    y -= value.y;
}

Vector2 Vector2::operator*(const int value) const
{
    return Vector2(x * value, y * value);
}

void Vector2::operator*=(const int value)
{
    x *= value;
    y *= value;
}

Vector2 Vector2::operator/(const int value) const
{
    return Vector2(x / value, y / value);
}

void Vector2::operator/=(const int value)
{
    x /= value;
    y /= value;
}

Vector2F::Vector2F(void)
{
    x = 0.0f;
    y = 0.0f;
}

Vector2F::Vector2F(float positionX, float positionY)
{
    x = positionX;
    y = positionY;
}

Vector2F::~Vector2F(void)
{
}

Vector2F Vector2F::operator+(const Vector2F value) const
{
    return Vector2F(x + value.x, y + value.y);
}

void Vector2F::operator+=(const Vector2F value)
{
    x += value.x;
    y += value.y;
}

Vector2F Vector2F::operator-(const Vector2F value) const
{
    return Vector2F(x - value.x, y - value.y);
}

void Vector2F::operator-=(const Vector2F value)
{
    x -= value.x;
    y -= value.y;
}

Vector2F Vector2F::operator*(const float value) const
{
    return Vector2F(x * value, y * value);
}

void Vector2F::operator*=(const float value)
{
    x *= value;
    y *= value;
}

Vector2F Vector2F::operator/(const float value) const
{
    return Vector2F(x / value, y / value);
}

void Vector2F::operator/=(const float value)
{
    x /= value;
    y /= value;
}