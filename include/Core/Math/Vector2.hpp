#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "Math.hpp"

namespace Scramble
{
    class Vector2
    {
    public:
        float x, y;

    public:
        Vector2();
        Vector2(float x, float y);

    public:
        static Vector2 Up;
        static Vector2 Down;
        static Vector2 Left;
        static Vector2 Right;

    public:
        Vector2 operator +(Vector2 v);
        Vector2 operator -(Vector2 v);
        Vector2 operator =(Vector2 v);
        Vector2 operator *(float value);
        Vector2 operator /(float value);
        
    public:
        void operator +=(Vector2 v);
        void operator -=(Vector2 v);
        void operator *=(float value);
        void operator /=(float value);

    private:
        bool operator ==(Vector2 v);
        bool operator !=(Vector2 v);

    public:
        static float Magnitude(Vector2 v);
        static float Dot(Vector2 v1, Vector2 v2);
        static float Distance(Vector2 v1, Vector2 v2);
        static float Angle(Vector2 v1, Vector2 v2);

    public:
        static Vector2 Normalize(Vector2 v);
        static Vector2 Lerp(Vector2 start, Vector2 end, float t);
    };
}

#endif