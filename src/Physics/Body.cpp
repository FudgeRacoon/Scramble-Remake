#include "Physics/Body.hpp"
using namespace Scramble::Physics;

Body::Body(Vector3 position, Vector3 rotation)
{
    BodyDef bodyDef;

    position = position / PhysicsSystem::PTM_RATIO;

    bodyDef.position = position;
    bodyDef.rotation = rotation;

    bodyDef.type = BodyType::DYNAMIC;

    bodyDef.linearDamping = 0.3f;
    bodyDef.angularDamping = 0.3f;
    bodyDef.gravityScale = 1.0f;

    bodyDef.fixedRotation = false;
    bodyDef.continousCollision = true;

    PhysicsSystem::CreateBody(this, bodyDef);
}
Body::Body(Vector3 position, Vector3 rotation, BodyType bodyType)
{
    BodyDef bodyDef;

    position = position / PhysicsSystem::PTM_RATIO;

    bodyDef.position = position;
    bodyDef.rotation = rotation;

    bodyDef.type = bodyType;

    bodyDef.linearDamping = 0.3f;
    bodyDef.angularDamping = 0.3f;
    bodyDef.gravityScale = 1.0f;

    bodyDef.fixedRotation = false;
    bodyDef.continousCollision = true;

    PhysicsSystem::CreateBody(this, bodyDef);
}
Body::Body(Vector3 position, Vector3 rotation, Vector3 initialVelocity)
{
    BodyDef bodyDef;

    position = position / PhysicsSystem::PTM_RATIO;

    bodyDef.position = position;
    bodyDef.rotation = rotation;
    
    bodyDef.linearVelocity = initialVelocity / PhysicsSystem::PTM_RATIO;

    bodyDef.type = BodyType::DYNAMIC;

    bodyDef.linearDamping = 0.3f;
    bodyDef.angularDamping = 0.3f;
    bodyDef.gravityScale = 1.0f;

    bodyDef.fixedRotation = false;
    bodyDef.continousCollision = true;

    PhysicsSystem::CreateBody(this, bodyDef);
}

Body::~Body()
{
    PhysicsSystem::RemoveBody(this);
}

I32 Body::GetFixtureListSize()
{
    I32 size = 0;
    b2Fixture* fixture = this->nativeBody->GetFixtureList();
    
    while(fixture) 
    {
        size++;
        fixture = fixture->GetNext();
    }

    return size;
}

b2Body* Body::GetNativeBody()
{
    return this->nativeBody;
}
b2Fixture* Body::GetNativeFixture()
{
    return this->nativeFixture;
}

void Body::SetNativeBody(b2Body* value)
{
    this->nativeBody = value;
}
void Body::SetNativeFixture(b2Fixture* value)
{
    this->nativeFixture = value;
}

void Body::AddBoxFixture(Bounds bounds, 
                F32 mass, F32 friction, F32 restitution, bool isTrigger)
{
    b2FixtureDef natvieFixtureDef;

    b2PolygonShape shape;
            
    Vector3 center = bounds.GetCenter() / PhysicsSystem::PTM_RATIO;
    Vector3 extents = bounds.GetExtents() / PhysicsSystem::PTM_RATIO;
    
    shape.SetAsBox(extents.x, extents.y, b2Vec2(center.x, center.y), 0.0);
    natvieFixtureDef.shape = &shape;

    natvieFixtureDef.friction = friction;
    natvieFixtureDef.restitution = restitution;
    natvieFixtureDef.density = 1.0f; //[TODO] Calculate density using mass and area

    natvieFixtureDef.isSensor = isTrigger;

    this->nativeBody->CreateFixture(&natvieFixtureDef);
    this->nativeFixture = this->nativeBody->GetFixtureList();
}
void Body::AddCircleFixture(Vector3 position, F32 radius, 
                F32 mass, F32 friction, F32 restitution, bool isTrigger)
{
    b2FixtureDef natvieFixtureDef;

    b2CircleShape shape;

    Vector3 _position = position / PhysicsSystem::PTM_RATIO;     

    shape.m_p.Set(_position.x, _position.y);
    shape.m_radius = radius;
    natvieFixtureDef.shape = &shape;

    natvieFixtureDef.friction = friction;
    natvieFixtureDef.restitution = restitution;
    natvieFixtureDef.density = 1.0f; //[TODO] Calculate density using mass and area

    natvieFixtureDef.isSensor = isTrigger;

    this->nativeBody->CreateFixture(&natvieFixtureDef);
    this->nativeFixture = this->nativeBody->GetFixtureList();
}

void Body::ResetFixture()
{
    int size = GetFixtureListSize();

    for(int i = 0; i < size; i++)
    {
        b2Fixture* toDestroy = this->nativeFixture;
        this->nativeFixture = this->nativeBody->GetFixtureList()->GetNext();
        this->nativeBody->DestroyFixture(toDestroy);
    }
}