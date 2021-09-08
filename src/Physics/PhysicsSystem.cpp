#include "Physics/PhysicsSystem.hpp"
using namespace Scramble::Physics;

#include "Physics/Body.hpp"

UniquePtr<b2World> PhysicsSystem::physicsWorld = nullptr;

Vector2 PhysicsSystem::globalGravity;

F32 PhysicsSystem::timeStep = 0.0;
F32 PhysicsSystem::accumulator = 0.0;
I32 PhysicsSystem::positionIterations = 0;
I32 PhysicsSystem::velocityIterations = 0;

void PhysicsSystem::OnStartUp(Vector3 gravity, F32 timeStep)
{
    PhysicsSystem::globalGravity = gravity;
    
    PhysicsSystem::timeStep = timeStep;
    PhysicsSystem::positionIterations = 5;
    PhysicsSystem::velocityIterations = 8;

    PhysicsSystem::physicsWorld = UniquePtr<b2World>(new b2World(b2Vec2(globalGravity.x, globalGravity.y)));
}
void PhysicsSystem::OnShutDown()
{
    physicsWorld.reset();
}

void PhysicsSystem::CreateBody(Body* body, BodyDef& bodyDef)
{
    b2BodyDef nativeBodyDef;

    nativeBodyDef.position.Set(bodyDef.position.x, bodyDef.position.y);
    nativeBodyDef.angle = bodyDef.rotation.z;
        
    nativeBodyDef.linearVelocity.Set(bodyDef.linearVelocity.x, bodyDef.linearVelocity.y);
    nativeBodyDef.angularDamping = bodyDef.angularVelocity.z;

    switch(bodyDef.type)
    {
        case BodyType::STATIC:    nativeBodyDef.type = b2BodyType::b2_staticBody; break;
        case BodyType::DYNAMIC:   nativeBodyDef.type = b2BodyType::b2_dynamicBody; break;
        case BodyType::KINEMATIC: nativeBodyDef.type = b2BodyType::b2_kinematicBody; break;
    }

    nativeBodyDef.linearDamping = bodyDef.linearDamping;
    nativeBodyDef.angularDamping = bodyDef.angularDamping;
    nativeBodyDef.gravityScale = bodyDef.gravityScale;

    nativeBodyDef.fixedRotation = bodyDef.fixedRotation;
    nativeBodyDef.bullet = bodyDef.continousCollision;

    nativeBodyDef.awake = bodyDef.awake;
    nativeBodyDef.enabled = bodyDef.enabled;
    nativeBodyDef.allowSleep = bodyDef.allowSleep;

    b2Body* nativeBody = physicsWorld->CreateBody(&nativeBodyDef);
    
    body->SetNativeBody(nativeBody);
}
void PhysicsSystem::RemoveBody(Body* body)
{
    physicsWorld->DestroyBody(body->GetNativeBody());
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

