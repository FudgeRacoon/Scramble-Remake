#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "Core/Common/Types.hpp"
#include "Core/Debug/Assert.hpp"
#include "Core/Math/Vector3.hpp"

#include "Physics/Body.hpp"

#include "../Entity.hpp"
#include "../Component.hpp"
#include "Transform.hpp"

using namespace Scramble;
using namespace Scramble::Physics;

namespace Scramble::Scene
{   
    struct BodyProps
    {
        Vector3 linearVelocity;
        Vector3 angularVelocity;

        BodyType type;

        F32 linearDrag;
        F32 angularDrag;
        F32 gravityScale;
        
        bool fixedRotation;
        bool continuousCollison;
    };

    enum ForceMode
    {
        FORCE = 0,
        IMPULSE
    };

    class RigidBody : public Component
    {
    private:
        Body* body;
        Transform* transform;

    private:
        BodyProps props;

    public:
        RigidBody(Entity* owner);
        RigidBody(Entity* owner, BodyType bodyType);
        RigidBody(Entity* owner, Vector3 initialVelocity);

    public:
        ~RigidBody();

    public:
        Body* GetBody();

    public:
        F32 GetLinearDrag();
        F32 GetAngularDrag();
        F32 GetGravityScale();
    
    public:
        BodyType GetType();

    public:
        Vector3 GetLinearVelocity();
        Vector3 GetAngularVelocity();

    public:        
        bool IsFixedRotation();
        bool IsContinousCollision();

    public:
        void SetLinearDrag(F32 value);
        void SetAngularDrag(F32 value);
        void SetGravityScale(F32 value);

    public:
        void SetType(BodyType type);

    public: 
        void SetLinearVelocity(Vector3 value);
        void SetAngularVelocity(Vector3 value);

    public:   
        void SetFixedRotation(bool value);
        void SetContinousCollision(bool value);

    public:
        void AddForce(Vector3 force, ForceMode mode);
        void AddTorque(F32 torque, ForceMode mode = ForceMode::FORCE);

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif