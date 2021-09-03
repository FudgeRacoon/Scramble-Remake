#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <string.h>

#include "Vector3.hpp"
#include "Vector4.hpp"

#include "Utils/Utility.hpp"

namespace Scramble
{
    class Matrix4
    {
    private:
        float* data;

    public:
        Matrix4();
        Matrix4(Vector4 r0, Vector4 r1, Vector4 r2, Vector4 r3);
        Matrix4(const Matrix4& m);
        Matrix4(Matrix4&& m);
    
    public:
        ~Matrix4();

    public:
        Matrix4 operator *(Matrix4 m);
        Vector4 operator *(Vector4 v);
        
    public:
        Matrix4 operator =(Matrix4 m);
        float& operator ()(int row, int column);

    public:
        const float* GetRawData();

    public:
        static Matrix4 Identity();
        static Matrix4 Inverse(Matrix4 m);

    public:
        static Matrix4 Transalte(Vector3 translate);
        static Matrix4 Scale(Vector3 scale);
        static Matrix4 Rotate(float angle, Vector3 axis);
        static Matrix4 Transform(Vector3 translate, Vector3 scale, Vector3 rotation);

    public:
        static Matrix4 LookAt(Vector3 position, Vector3 target, Vector3 up);
        static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);        
    };
}

#endif