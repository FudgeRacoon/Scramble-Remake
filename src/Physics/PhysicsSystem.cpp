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
    b2Body* body = nullptr;
    Transform* transform = rigidbody->ownerTransform;

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polygonShape;

    bodyDef.position.Set(
        transform->position.x / PhysicsSystem::PPM, 
        transform->position.y / PhysicsSystem::PPM
    );
    bodyDef.angle = transform->rotation.z;

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

    body = physicsWorld->CreateBody(&bodyDef);
    
    Vector3 size = collider->GetSize() / PhysicsSystem::PPM;
    Vector3 center = collider->GetCenter() / PhysicsSystem::PPM;
    Vector3 extents = collider->GetExtents() / PhysicsSystem::PPM;

    polygonShape.SetAsBox(extents.x, extents.y, b2Vec2(center.x, center.y), 0.0);
    
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = rigidbody->props.mass / (size.x * size.y);

    body->CreateFixture(&fixtureDef);

    collider->nativeShape = dynamic_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());
    
    rigidbody->nativeBody = body;
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