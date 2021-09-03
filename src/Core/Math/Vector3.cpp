#include "Core/Math/Vector3.hpp"
using namespace Scramble;

const Vector3 Vector3::Up = Vector3(0.0, 1.0, 0.0);
const Vector3 Vector3::Down = Vector3(0.0, -1.0, 0.0);
const Vector3 Vector3::Left = Vector3(-1.0, 0.0, 0.0);
const Vector3 Vector3::Right = Vector3(1.0, 0.0, 0.0);
const Vector3 Vector3::Forward = Vector3(0.0, 0.0, 1.0);

Vector3::Vector3()
    :x(0.0), y(0.0), z(0.0) {}
Vector3::Vector3(float x, float y, float z)
    :x(x), y(y), z(z)  {}

Vector3 Vector3::operator +(Vector3 v)
{
    return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}
Vector3 Vector3::operator -(Vector3 v)
{
    return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}
Vector3 Vector3::operator =(Vector3 v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;

    return *this;
}
Vector3 Vector3::operator *(float value)
{
    return Vector3(this->x * value, this->y * value, this->z * value);
}
Vector3 Vector3::operator /(float value)
{
    return Vector3(this->x / value, this->y / value, this->z / value);
}

void Vector3::operator +=(Vector3 v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
}
void Vector3::operator -=(Vector3 v)
{
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
}
void Vector3::operator *=(float value)
{
    this->x *= value;
    this->y *= value;
    this->z *= value;
}
void Vector3::operator /=(float value)
{
    this->x /= value;
    this->y /= value;
    this->z /= value;
}

bool Vector3::operator ==(Vector3 v)
{
    return this->x == v.x && this->y == v.y && this->z == v.z;
}
bool Vector3::operator !=(Vector3 v)
{
    return this->x != v.x || this->y != v.y || this->z != v.z;
}

Vector3::operator Vector2()
{
    return Vector2(this->x, this->y);
}

float Vector3::Magnitude(Vector3 v)
{
    return Math::Sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
float Vector3::Dot(Vector3 v1, Vector3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
float Vector3::Distance(Vector3 v1, Vector3 v2)
{
    float diffX = v2.x - v1.x;
    float diffY = v2.y - v1.y;
    float diffZ = v2.z - v1.z;

    return Magnitude(Vector3(diffX, diffY, diffZ));
}
float Vector3::Angle(Vector3 v1, Vector3 v2)
{
    float lhs = Dot(v1, v2) / (Magnitude(v1) * Magnitude(v2));
    return Math::Acos(lhs);
}

Vector3 Vector3::Negate(Vector3 v)
{
    return Vector3(-v.x, -v.y, -v.z);
}
Vector3 Vector3::Normalize(Vector3 v)
{
    return v / Magnitude(v);
}
Vector3 Vector3::Cross(Vector3 v1, Vector3 v2)
{
    return Vector3((v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x));
}
Vector3 Vector3::Lerp(Vector3 start, Vector3 end, float t)
{
    return start + ((end - start) * Math::Clamp(t, 0.0, 1.0));
}