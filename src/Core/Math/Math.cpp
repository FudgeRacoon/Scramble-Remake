#include "Core/Math/Math.hpp"
using namespace Scramble;

float Math::Cos(float value)
{
    return static_cast<float>(cos(value));
}
float Math::Sin(float value)
{
    return static_cast<float>(sin(value));
}
float Math::Tan(float value)
{
    return static_cast<float>(tan(value));
}
float Math::Acos(float value)
{   
    return static_cast<float>(acos(value));
}
float Math::Asin(float value)
{
    return static_cast<float>(cos(value));
}
float Math::Atan2(float y, float x)
{
    return static_cast<float>(atan2(y, x));
}
float Math::Abs(float value)
{
    return value < 0 ? -(value) : value;
}
float Math::Sqrt(float value)
{
    return static_cast<float>(sqrt(value));
}
float Math::Pow(float value, float power)
{
    return static_cast<float>(pow(value, power));
}
float Math::Max(float a, float b)
{
    return a > b ? a : b;
}
float Math::Min(float a, float b)
{   
    return a < b ? a : b;
}
float Math::Clamp(float value, float min, float max)
{
    if(value < min)
        value = min;
    else if(value > max)
        value = max;
    
    return value;
}
float Math::Lerp(float a, float b, float t)
{
    return a + ((b - a) * Clamp(t, 0.0, 1.0));
}
float Math::RadToDegree(float value)
{
    return value * (180.0 / PI);
}
float Math::DegreeToRad(float value)
{
    return value * (PI / 180.0);
}
float Math::Ceil(float value)
{
    return static_cast<float>(ceil(value));
}
float Math::Floor(float value)
{
    return static_cast<float>(floor(value));
}
int Math::Round(float value)
{
    return value > 0 ? (int)(value + 0.5) : (int)(value - 0.5);
}