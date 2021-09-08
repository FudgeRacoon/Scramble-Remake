#ifndef BODY_HPP
#define BODY_HPP

#include "Core/Common/Types.hpp"
#include "Core/Math/Vector3.hpp"

#include "BodyType.hpp"
#include "Bounds.hpp"
#include "PhysicsSystem.hpp"

using namespace Scramble;

namespace Scramble::Physics
{
    struct BodyDef
    {
        Vector3 position;
        Vector3 rotation;
        
        Vector3 linearVelocity;
        Vector3 angularVelocity;
        
        BodyType type;

        F32 linearDamping;
        F32 angularDamping;
        F32 gravityScale;
        
        bool fixedRotation;
        bool continousCollision;

        bool awake = true;
        bool enabled = true;
        bool allowSleep = true;
    };

    class Body
    {
    private:
        b2Body* nativeBody;
        b2Fixture* nativeFixture;

    public:
        Body(Vector3 position, Vector3 rotation);
        Body(Vector3 position, Vector3 rotation, BodyType bodyType);
        Body(Vector3 position, Vector3 rotation, Vector3 initialVelocity);

    public:
        ~Body();

    public:
        I32 GetFixtureListSize();
    
    public:
        b2Body* GetNativeBody();
        b2Fixture* GetNativeFixture();

    public:
        void SetNativeBody(b2Body* value);
        void SetNativeFixture(b2Fixture* value);

    public:
        void AddBoxFixture(Bounds bounds, 
                    F32 mass = 1.0f, F32 friction = 0.2f, F32 restitution = 0.1f, bool isTrigger = false);
        void AddCircleFixture(Vector3 position, F32 radius, 
                    F32 mass = 1.0f, F32 friction = 0.2f, F32 restitution = 0.1f, bool isTrigger = false);
        
    public:
        void ResetFixture();
    };
}

#endif