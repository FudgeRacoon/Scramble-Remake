#include "Physics/PhysicsSystem.hpp"
using namespace Scramble::Physics;

b2World* PhysicsSystem::physicsWorld = nullptr;

Vector2 PhysicsSystem::globalGravity = Vector2();

F32 PhysicsSystem::timeStep = 0.0;
F32 PhysicsSystem::accumulator = 0.0;

I32 PhysicsSystem::positionIterations = 0;
I32 PhysicsSystem::velocityIterations = 0;

void PhysicsSystem::OnStartUp(Vector2 gravity, F32 timeStep)
{
    PhysicsSystem::globalGravity = gravity;
    
    PhysicsSystem::timeStep = timeStep;

    PhysicsSystem::positionIterations = 3;
    PhysicsSystem::velocityIterations = 8;

    PhysicsSystem::physicsWorld = new b2World(b2Vec2(globalGravity.x, globalGravity.y));
}
void PhysicsSystem::OnShutDown()
{
    delete physicsWorld;
}

void PhysicsSystem::FixedUpdate()
{
    accumulator += Time::GetDeltaTime();

    while(accumulator >= timeStep)
    {
        accumulator -= timeStep;
        physicsWorld->Step(timeStep, velocityIterations, positionIterations);
    }
}