#include "Scene/Components/RigidBody.hpp"
using namespace Scramble::Scene;

RigidBody::RigidBody(Entity* owner) : Component(owner)
{
    this->nativeBody = nullptr;

    this->props.mass = 10.0;
    this->props.linearDrag = 0.5;
    this->props.angularDrag = 0.5;
    this->props.gravityScale = 1.0;

    this->props.bodyType = BodyType::DYNAMIC;
    
    this->props.fixedRotation = false;
    this->props.continuousCollison = true;

    this->ownerTransform = this->owner->GetComponent<Transform>();
    
    this->owner->AddComponent<BoxCollider>();
    
    PhysicsSystem::AddBody(this, this->owner->GetComponent<BoxCollider>());
}
RigidBody::RigidBody(Entity* owner, BodyType bodyType, F32 mass) : Component(owner)
{
    this->nativeBody = nullptr;

    this->props.mass = mass;
    this->props.linearDrag = 0.5;
    this->props.angularDrag = 0.5;
    this->props.gravityScale = 1.0;

    this->props.bodyType = bodyType;
    
    this->props.fixedRotation = false;
    this->props.continuousCollison = true;

    this->ownerTransform = this->owner->GetComponent<Transform>();

    this->owner->AddComponent<BoxCollider>();

    PhysicsSystem::AddBody(this, this->owner->GetComponent<BoxCollider>());
}

F32 RigidBody::GetMass()
{
    return this->props.mass;
}
F32 RigidBody::GetLinearDrag()
{
    return this->props.linearDrag;
}
F32 RigidBody::GetAngularDrag()
{
    return this->props.angularDrag;
}
F32 RigidBody::GetGravityScale()
{
    return this->props.gravityScale;
}
        
Vector3 RigidBody::GetVelocity()
{
    return this->props.velocity;
}
        
bool RigidBody::IsFixedRotation()
{
    return this->props.fixedRotation;
}
bool RigidBody::IsContinousCollision()
{
    return this->props.continuousCollison;
}

void RigidBody::SetMass(F32 value)
{
    this->props.mass = value;
}
void RigidBody::SetLinearDrag(F32 value)
{
    this->props.linearDrag = value;
    this->nativeBody->SetLinearDamping(value);
}
void RigidBody::SetAngularDrag(F32 value)
{
    this->props.angularDrag = value;
    this->nativeBody->SetAngularDamping(value);
}
void RigidBody::SetGravityScale(F32 value)
{
    this->props.gravityScale = value;
    this->nativeBody->SetGravityScale(value);
}
 
void RigidBody::SetVelocity(Vector3 value)
{
    this->props.velocity = value;
    this->nativeBody->SetLinearVelocity(b2Vec2(value.x, value.y));
}
        
void RigidBody::SetFixedRotation(bool value)
{
    this->props.fixedRotation = value;
    this->nativeBody->SetFixedRotation(value);
}
void RigidBody::SetContinousCollision(bool value)
{
    this->props.continuousCollison = value;
    this->nativeBody->SetBullet(value);
}

void RigidBody::Setup()
{
    
}
void RigidBody::Update()
{
    b2Vec2 nativeVelocity = this->nativeBody->GetLinearVelocity();
    this->props.velocity = Vector3(nativeVelocity.x, nativeVelocity.y, 0.0);

    this->ownerTransform->position.x = this->nativeBody->GetPosition().x * PhysicsSystem::PPM;
    this->ownerTransform->position.y = this->nativeBody->GetPosition().y * PhysicsSystem::PPM;
    this->ownerTransform->rotation.z = this->nativeBody->GetAngle();
}