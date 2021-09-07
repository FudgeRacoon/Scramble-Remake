#ifndef PHYSICS_WORLD_HPP
#define PHYSICS_WORLD_HPP

#include "Box2D/include/box2d/box2d.h"

#include "Core/Common/Types.hpp"
#include "Core/Time/Time.hpp"
#include "Core/Math/Vector3.hpp"

namespace Scramble::Scene
{
    class RigidBody;
    class BoxCollider;
}

using namespace Scramble;
using namespace Scramble::Scene;

namespace Scramble::Physics
{
    class PhysicsSystem
    {
    public:
        static constexpr F32 PPM = 64.0;

    private:
        static b2World* physicsWorld;
    
    private:
        static Vector2 globalGravity;
    
    private:
        static F32 timeStep;
        static F32 accumulator;
        static I32 positionIterations;
        static I32 velocityIterations;

    public:
        static void OnStartUp(Vector3 gravity, F32 timeStep);
        static void OnShutDown();

    public:
        static void AddBody(RigidBody* rigidbody, BoxCollider* collider);

    public:
        static void FixedUpdate();
    };
}

#endif