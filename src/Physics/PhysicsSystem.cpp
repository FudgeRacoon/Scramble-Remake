#include "Physics/PhysicsSystem.hpp"
using namespace Scramble::Physics;

#include "Scene/Components/Transform.hpp"
#include "Scene/Components/RigidBody.hpp"
#include "Scene/Components/BoxCollider.hpp"

b2World* PhysicsSystem::physicsWorld = nullptr;

Vector2 PhysicsSystem::globalGravity = Vector2();

F32 PhysicsSystem::timeStep = 0.0;
F32 PhysicsSystem::accumulator = 0.0;
I32 PhysicsSystem::positionIterations = 0;
I32 PhysicsSystem::velocityIterations = 0;

I32 PhysicsSystem::Internal_FixtureListSize(RigidBody* rigidbody)
{
    I32 size = 0;
    b2Fixture* fixture = rigidbody->nativeBody->GetFixtureList();
    
    while(fixture) 
    {
        size++;
        fixture = fixture->GetNext();
    }

    return size;
}

b2BodyDef PhysicsSystem::Internal_CreateBodyDef(RigidBody* rigidbody)
{
    b2BodyDef bodyDef;

    Vector3 position = rigidbody->ownerTransform->position / PTM_RATIO;
    Vector3 rotation = rigidbody->ownerTransform->rotation;

    bodyDef.position.Set(position.x, position.y);
    bodyDef.angle = rotation.z;

    bodyDef.linearDamping = rigidbody->props.linearDrag;
    bodyDef.angularDamping = rigidbody->props.angularDrag;
    bodyDef.gravityScale = rigidbody->props.gravityScale;

    switch(rigidbody->props.bodyType)
    {
        case BodyType::STATIC:    bodyDef.type = b2BodyType::b2_staticBody; break;
        case BodyType::DYNAMIC:   bodyDef.type = b2BodyType::b2_dynamicBody; break;
        case BodyType::KINEMATIC: bodyDef.type = b2BodyType::b2_kinematicBody; break;
    }

    bodyDef.fixedRotation = rigidbody->props.fixedRotation;
    bodyDef.bullet = rigidbody->props.continuousCollison;

    return bodyDef;
}

void PhysicsSystem::OnStartUp(Vector3 gravity, F32 timeStep)
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

void PhysicsSystem::AddBody(RigidBody* rigidbody, BoxCollider* collider)
{
    b2BodyDef bodyDef = Internal_CreateBodyDef(rigidbody);
    b2Body* body = physicsWorld->CreateBody(&bodyDef);
    
    rigidbody->nativeBody = body;

    if(collider)
        AddBoxCollider(rigidbody, collider);
}
void PhysicsSystem::RemoveBody(RigidBody* rigidbody)
{
    physicsWorld->DestroyBody(rigidbody->nativeBody);
}
void PhysicsSystem::RemoveFixture(RigidBody* rigidbody)
{
    int size = Internal_FixtureListSize(rigidbody);

    for(int i = 0; i < size; i++)
        rigidbody->nativeBody->DestroyFixture(
            rigidbody->nativeBody->GetFixtureList()
        );
}

void PhysicsSystem::AddBoxCollider(RigidBody* rigidbody, BoxCollider* collider)
{
    b2PolygonShape shape;
    b2FixtureDef fixtureDef;

    Vector3 size = collider->GetSize() / PTM_RATIO;
    Vector3 center = collider->GetCenter() / PTM_RATIO;
    Vector3 extents = collider->GetExtents() / PTM_RATIO;

    shape.SetAsBox(extents.x, extents.y, b2Vec2(size.x, size.y), 0);

    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0;
    fixtureDef.friction = Math::Clamp(collider->GetFriction(), 0.0, 1.0);
    fixtureDef.restitution = Math::Clamp(collider->GetResistution(), 0.0, 1.0);
    fixtureDef.isSensor = collider->IsTrigger();

    rigidbody->nativeBody->CreateFixture(&fixtureDef);
}

void PhysicsSystem::ResetBoxCollider(RigidBody* rigidbody, BoxCollider* collider)
{
    int size = Internal_FixtureListSize(rigidbody);

    for(int i = 0; i < size; i++)
        rigidbody->nativeBody->DestroyFixture(
            rigidbody->nativeBody->GetFixtureList()
        );

    AddBoxCollider(rigidbody, collider);
}

void PhysicsSystem::SetSensor(RigidBody* rigidbody, bool value)
{
    b2Fixture* fixture = rigidbody->nativeBody->GetFixtureList();

    while(fixture)
    {
        fixture->SetSensor(value);
        fixture = fixture->GetNext();
    }
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