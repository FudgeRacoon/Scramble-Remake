#include "Core/Math/Vector2.hpp"
using namespace Scramble;

const Vector2 Vector2::Up = Vector2(0.0, 1.0);
const Vector2 Vector2::Down = Vector2(0.0, -1.0);
const Vector2 Vector2::Left = Vector2(-1.0, 0.0);
const Vector2 Vector2::Right = Vector2(1.0, 1.0);

Vector2::Vector2()
    :x(0.0), y(0.0) {}
Vector2::Vector2(float x, float y)
    :x(x), y(y) {}

Vector2 Vector2::operator +(Vector2 v)
{
    return Vector2(this->x + v.x, this->y + v.y);
}
Vector2 Vector2::operator -(Vector2 v)
{
    return Vector2(this->x - v.x, this->y - v.y);
}
Vector2 Vector2::operator =(Vector2 v)
{
    this->x = v.x;
    this->y = v.y;

    return *this;
}
Vector2 Vector2::operator *(float value)
{
    return Vector2(this->x * value, this->y * value);
}
Vector2 Vector2::operator /(float value)
{
    return Vector2(this->x / value, this->y / value);
}

void Vector2::operator +=(Vector2 v)
{
    this->x += v.x;
    this->y += v.y;
}
void Vector2::operator -=(Vector2 v)
{
    this->x -= v.x;
    this->y -= v.y;
}
void Vector2::operator *=(float value)
{
    this->x *= value;
    this->y *= value;
}
void Vector2::operator /=(float value)
{
    this->x /= value;
    this->y /= value;
}

bool Vector2::operator ==(Vector2 v)
{
    return this->x == v.x && this->y == v.y;
}
bool Vector2::operator !=(Vector2 v)
{
    return this->x != v.x || this->y != v.y;
}

float Vector2::Magnitude(Vector2 v)
{
    return Math::Sqrt((v.x * v.x) + (v.y * v.y));
}
float Vector2::Dot(Vector2 v1, Vector2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}
float Vector2::Distance(Vector2 v1, Vector2 v2)
{
    float diffX = v2.x - v1.x;
    float diffY = v2.y - v1.y;

    return Magnitude(Vector2(diffX, diffY));
}
float Vector2::Angle(Vector2 v1, Vector2 v2)
{
    float lhs = Dot(v1, v2) / (Magnitude(v1) * Magnitude(v2));
    return Math::Acos(lhs);
}

Vector2 Vector2::Normalize(Vector2 v)
{
    return v / Magnitude(v);
}
Vector2 Vector2::Lerp(Vector2 start, Vector2 end, float t)
{
    return start + ((end - start) * Math::Clamp(t, 0.0, 1.0));
}