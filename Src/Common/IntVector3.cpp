#include "IntVector3.h"
#include <tuple>
#include "../Utility/Utility.h"

IntVector3::IntVector3(void)
{
    x = 0;
    y = 0;
    z = 0;
}

IntVector3::IntVector3(int valueX, int valueY, int valueZ)
{
    x = valueX;
    y = valueY;
    z = valueZ;
}

IntVector3::IntVector3(VECTOR vector)
{
    x = Utility::Round(vector.x);
    y = Utility::Round(vector.y);
    z = Utility::Round(vector.z);
}

IntVector3::~IntVector3(void)
{
}

bool IntVector3::operator<(const IntVector3& value) const
{
    return std::tie(x, y, z) < std::tie(value.x, value.y, value.z);
}

void IntVector3::Add(int value)
{
    x += value;
    y += value;
    z += value;
}

void IntVector3::Sub(int value)
{
    x -= value;
    y -= value;
    z -= value;
}

void IntVector3::Scale(int value)
{
    x *= value;
    y *= value;
    z *= value;
}