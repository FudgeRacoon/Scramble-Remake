#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "Box2D/include/box2d/box2d.h"

#include "Core/Common/Types.hpp"
#include "Core/Math/Vector3.hpp"

#include "Physics/BodyType.hpp"

#include "Transform.hpp"
#include "../Component.hpp"
using namespace Scramble;
using namespace Scramble::Physics;

namespace Scramble::Scene
{
    class RigidBody : public Component
    {
    private:
        b2Body* rawBody;
        Transform* ownerTransform;
    
    public:
        BodyType bodyType;

    public:
        Vector3 velocity;

    public:
        F32 mass;
        F32 linearDrag;
        F32 angularDrag;

    public:
        bool fixedRotation;
        bool continuousCollison;

    public:
        RigidBody();
        RigidBody(BodyType bodyType, F32 mass);

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif