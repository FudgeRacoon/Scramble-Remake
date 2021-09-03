#ifndef MATH_HPP
#define MATH_HPP

#include <math.h>

namespace Scramble
{
    class Math
    {
    public:
        static constexpr float PI = 3.14159265359;
        static constexpr float EPSILON = __FLT_EPSILON__;
        static constexpr float POSITIVE_INFINITY = __FLT_MAX__;
        static constexpr float NEGATIVE_INFINITY = -(__FLT_MAX__);

    public:
        static float Cos(float value);
        static float Sin(float value);
        static float Tan(float value);
        static float Acos(float value);
        static float Asin(float value);
        static float Atan2(float y, float x);
        static float Abs(float value);
        static float Sqrt(float value);
        static float Pow(float value, float power);
        static float Max(float a, float b);
        static float Min(float a, float b);
        static float Clamp(float value, float min, float max);
        static float Lerp(float a, float b, float t);
        static float RadToDegree(float value);
        static float DegreeToRad(float value);
        static float Ceil(float value);
        static float Floor(float value);
        static int Round(float value);
    };
}

#endif