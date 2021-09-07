#ifndef BOUNDS_HPP
#define BOUNDS_HPP

#include "Core/Math/Vector3.hpp"
using namespace Scramble;

namespace Scramble::Physics
{
    class Bounds
    {
    private:
        Vector3 center;
        Vector3 extents;

    public:
        Bounds() = default;
        Bounds(Vector3 center, Vector3 size);

    public:
        bool operator ==(Bounds b);
        bool operator !=(Bounds b);

    public:
        Vector3 GetMin();
        Vector3 GetMax();
        Vector3 GetSize();
        Vector3 GetCenter();
        Vector3 GetExtents();

    public:
        void SetSize(Vector3 value);
        void SetCenter(Vector3 value);
        void SetExtents(Vector3 value);
    };
}

#endif