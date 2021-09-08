#ifndef PHYSICS_WORLD_HPP
#define PHYSICS_WORLD_HPP

#include "Box2D/include/box2d/box2d.h"

#include "Core/Common/Types.hpp"
#include "Core/Debug/Assert.hpp"
#include "Core/Time/Time.hpp"
#include "Core/Math/Math.hpp"
#include "Core/Math/Vector3.hpp"

using namespace Scramble;

namespace Scramble::Physics
{
    class Body;
    class BodyDef;

    class PhysicsSystem
    {
    public:
        static constexpr F32 PTM_RATIO = 64.0;

    private:
        static UniquePtr<b2World> physicsWorld;
    
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
        static void CreateBody(Body* body, BodyDef& bodyDef);
        static void RemoveBody(Body* body);

    public:
        static void FixedUpdate();
    };
}

#endif