#ifndef PHYSICS_WORLD_HPP
#define PHYSICS_WORLD_HPP

#include "Box2D/include/box2d/box2d.h"

#include "Core/Common/Types.hpp"
#include "Core/Time/Time.hpp"
#include "Core/Math/Vector2.hpp"
using namespace Scramble;

namespace Scramble::Physics
{
    class PhysicsSystem
    {
    private:
        static b2World* physicsWorld;
    
    private:
        static Vector2 globalGravity;
    
    private:
        static F32 timeStep;
        static F32 accumulator;

    private:
        static I32 positionIterations;
        static I32 velocityIterations;

    public:
        static void OnStartUp(Vector2 gravity, F32 timeStep);
        static void OnShutDown();

    public:
        static void FixedUpdate();
    };
}

#endif