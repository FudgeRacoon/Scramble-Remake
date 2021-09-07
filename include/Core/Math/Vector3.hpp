#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "Math.hpp"
#include "Vector2.hpp"

namespace Scramble
{
    class Vector3
    {
    public:
        float x, y, z;

    public:
        Vector3();
        Vector3(float x, float y, float z);

    public:
        static Vector3 Up;
        static Vector3 Down; 
        static Vector3 Left; 
        static Vector3 Right;        
        static Vector3 Forward;

    public:
        Vector3 operator +(Vector3 v);
        Vector3 operator -(Vector3 v);
        Vector3 operator =(Vector3 v);
        Vector3 operator *(float value);
        Vector3 operator /(float value);
        
    public:
        void operator +=(Vector3 v);
        void operator -=(Vector3 v);
        void operator *=(float value);
        void operator /=(float value);

    private:
        bool operator ==(Vector3 v);
        bool operator !=(Vector3 v);

    public:
        operator Vector2();

    public:
        static float Magnitude(Vector3 v);
        static float Dot(Vector3 v1, Vector3 v2);
        static float Distance(Vector3 v1, Vector3 v2);
        static float Angle(Vector3 v1, Vector3 v2);

    public:
        static Vector3 Negate(Vector3 v);
        static Vector3 Normalize(Vector3 v);
        static Vector3 Cross(Vector3 v1, Vector3 v2);
        static Vector3 Lerp(Vector3 start, Vector3 end, float t);
    };
}

#endif