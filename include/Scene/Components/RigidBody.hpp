#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "Core/Common/Types.hpp"
#include "Core/Math/Vector3.hpp"

#include "Physics/BodyType.hpp"
#include "Physics/PhysicsSystem.hpp"

#include "../Entity.hpp"
#include "../Component.hpp"
#include "Transform.hpp"

using namespace Scramble;
using namespace Scramble::Physics;

namespace Scramble::Scene
{   
    struct BodyProps
    {
        F32 mass;
        F32 linearDrag;
        F32 angularDrag;
        F32 gravityScale;
        
        Vector3 velocity;
        
        BodyType bodyType;
        
        bool fixedRotation;
        bool continuousCollison;
    };

    class RigidBody : public Component
    {
    private:
        b2Body* nativeBody;

    private:
        BodyProps props;

    private:
        Transform* ownerTransform;

    public:
        RigidBody();
        RigidBody(BodyType bodyType, F32 mass);

    public:
        F32 GetMass();
        F32 GetLinearDrag();
        F32 GetAngularDrag();
        F32 GetGravityScale();
        
    public:
        Vector3 GetVelocity();

    public:        
        bool IsFixedRotation();
        bool IsContinousCollision();

    public:
        void SetMass(F32 value);
        void SetLinearDrag(F32 value);
        void SetAngularDrag(F32 value);
        void SetGravityScale(F32 value);

    public: 
        void SetVelocity(Vector3 value);

    public:   
        void SetFixedRotation(bool value);
        void SetContinousCollision(bool value);

    public:
        void Setup() override;
        void Update() override;

    friend PhysicsSystem;
    };
}

#endif