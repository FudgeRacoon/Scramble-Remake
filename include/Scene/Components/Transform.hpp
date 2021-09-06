#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include "Core/Math/Vector3.hpp"

#include "../Component.hpp"

namespace Scramble::Scene
{
    class Transform : public Component
    {
    public:
        Vector3 positon;
        Vector3 rotation;
        Vector3 scale;

    public:
        Transform() = default;
        Transform(Vector3 positon, Vector3 rotation, Vector3 scale);

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif