#include "Core/Math/Vector4.hpp"
using namespace Scramble;

Vector4::Vector4() 
    : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
Vector4::Vector4(float x, float y, float z) 
    : x(x), y(y), z(z), w(1.0f) {}
Vector4::Vector4(float x, float y, float z, float w) 
    : x(x), y(y), z(z), w(w) {}

Vector4::operator Vector3()
{
    return Vector3(this->x, this->y, this->z);
}       