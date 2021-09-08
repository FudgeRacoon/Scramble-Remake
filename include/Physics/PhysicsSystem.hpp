#ifndef PHYSICS_WORLD_HPP
#define PHYSICS_WORLD_HPP

#include "Box2D/include/box2d/box2d.h"

#include "Core/Common/Types.hpp"
#include "Core/Debug/Assert.hpp"
#include "Core/Time/Time.hpp"
#include "Core/Math/Math.hpp"
#include "Core/Math/Vector3.hpp"

namespace Scramble::Scene
{
    class RigidBody;
    class BoxCollider;
    class CircleCollider;
}

using namespace Scramble;
using namespace Scramble::Scene;

namespace Scramble::Physics
{
    class PhysicsSystem
    {
    public:
        static constexpr F32 PTM_RATIO = 64.0;

    private:
        static b2World* physicsWorld;
    
    private:
        static Vector2 globalGravity;
    
    private:
        static F32 timeStep;
        static F32 accumulator;
        static I32 positionIterations;
        static I32 velocityIterations;

    private:
        static I32 Internal_FixtureListSize(RigidBody* rigidbody);
        
    private:
        static b2BodyDef Internal_CreateBodyDef(RigidBody* rigidbody);
        static b2FixtureDef Internal_CreateFixtureDef(BoxCollider* collider);

    public:
        static void OnStartUp(Vector3 gravity, F32 timeStep);
        static void OnShutDown();

    public:
        static void AddBody(RigidBody* rigidbody, BoxCollider* collider);
        static void RemoveBody(RigidBody* rigidbody);
        static void RemoveFixture(RigidBody* rigidbody);

    public:
        static void AddBoxCollider(RigidBody* rigidbody, BoxCollider* collider);
        static void AddCircleCollider(RigidBody* rigidbody, CircleCollider* collider);

    public:
        static void ResetBoxCollider(RigidBody* rigidbody, BoxCollider* collider);
        static void ResetCircleCollider(RigidBody* rigidbody, CircleCollider* collider);
    
    public:
        static void SetSensor(RigidBody* rigidbody, bool value);

    public:
        static void FixedUpdate();
    };
}

#endif