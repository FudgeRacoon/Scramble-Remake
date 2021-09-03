#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include "Vector3.hpp"

namespace Scramble
{
    class Vector4
    {
    public:
        float x, y, z, w;

    public:
        Vector4();
        Vector4(float x, float y, float z);
        Vector4(float x, float y, float z, float w);

    public:
        operator Vector3();     
    };
}

#endif