#include "Physics/Bounds.hpp"
using namespace Scramble::Physics;

Bounds::Bounds(Vector3 center, Vector3 size)
{
    this->center = center;
    this->extents = size * 0.5;
}   

bool Bounds::operator ==(Bounds b)
{
    return (this->center == b.center && this->extents == b.extents);
}
bool Bounds::operator !=(Bounds b)
{
    return !(*this == b);
}

Vector3 Bounds::GetMin()
{
    return this->center - this->extents;
}
Vector3 Bounds::GetMax()
{
    return this->center + this->extents;
}
Vector3 Bounds::GetSize()
{
    return this->extents * 2;
}
Vector3 Bounds::GetCenter()
{
    return this->center;
}
Vector3 Bounds::GetExtents()
{
    return this->extents;
}

void Bounds::SetSize(Vector3 value)
{
    this->extents = value * 0.5;
}
void Bounds::SetCenter(Vector3 value)
{
    this->center = value;
}
void Bounds::SetExtents(Vector3 value)
{
    this->extents = value;
}