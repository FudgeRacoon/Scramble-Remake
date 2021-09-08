#include "Scene/Components/RigidBody.hpp"
using namespace Scramble::Scene;

#include "Scene/Components/BoxCollider.hpp"

RigidBody::RigidBody(Entity* owner) : Component(owner)
{
    this->transform = owner->GetComponent<Transform>();
    this->body = new Body(this->transform->position, this->transform->rotation);
}
RigidBody::RigidBody(Entity* owner, BodyType bodyType) : Component(owner)
{
    this->transform = owner->GetComponent<Transform>();
    this->body = new Body(this->transform->position, this->transform->rotation, bodyType);
}
RigidBody::RigidBody(Entity* owner, Vector3 initialVelocity) : Component(owner)
{
    this->transform = owner->GetComponent<Transform>();
    this->body = new Body(this->transform->position, this->transform->rotation, initialVelocity);
}

RigidBody::~RigidBody()
{
    delete this->body;
    owner->RemoveComponent<BoxCollider>();
}

Body* RigidBody::GetBody()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->body;
}

F32 RigidBody::GetLinearDrag()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.linearDrag;
}
F32 RigidBody::GetAngularDrag()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.angularDrag;
}
F32 RigidBody::GetGravityScale()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.gravityScale;
}

BodyType RigidBody::GetType()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.type;
}

Vector3 RigidBody::GetLinearVelocity()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.linearVelocity;
}
Vector3 RigidBody::GetAngularVelocity()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.angularVelocity;
}
        
bool RigidBody::IsFixedRotation()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.fixedRotation;
}
bool RigidBody::IsContinousCollision()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.continuousCollison;
}

void RigidBody::SetLinearDrag(F32 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.linearDrag = value;
    this->body->GetNativeBody()->SetLinearDamping(value);
}
void RigidBody::SetAngularDrag(F32 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.angularDrag = value;
    this->body->GetNativeBody()->SetAngularDamping(value);
}
void RigidBody::SetGravityScale(F32 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.gravityScale = value;
    this->body->GetNativeBody()->SetGravityScale(value);
}

void RigidBody::SetType(BodyType type)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.type = type;

    switch(type)
    {
        case BodyType::STATIC:    this->body->GetNativeBody()->SetType(b2_staticBody); break;
        case BodyType::DYNAMIC:   this->body->GetNativeBody()->SetType(b2_dynamicBody); break;
        case BodyType::KINEMATIC: this->body->GetNativeBody()->SetType(b2_kinematicBody); break;
    }
}

void RigidBody::SetLinearVelocity(Vector3 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.linearVelocity = value;

    value /= PhysicsSystem::PTM_RATIO;
    this->body->GetNativeBody()->SetLinearVelocity(b2Vec2(value.x, value.y));
}
void RigidBody::SetAngularVelocity(Vector3 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.angularVelocity = value;

    value /= PhysicsSystem::PTM_RATIO;
    this->body->GetNativeBody()->SetAngularVelocity(value.x);
}
        
void RigidBody::SetFixedRotation(bool value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.fixedRotation = value;
    this->body->GetNativeBody()->SetFixedRotation(value);
}
void RigidBody::SetContinousCollision(bool value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.continuousCollison = value;
    this->body->GetNativeBody()->SetBullet(value);
}

void RigidBody::AddForce(Vector3 force, ForceMode mode)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    switch(mode)
    {
        case FORCE:   this->body->GetNativeBody()->ApplyForceToCenter(b2Vec2(force.x, force.y), true); break;
        case IMPULSE: this->body->GetNativeBody()->ApplyLinearImpulseToCenter(b2Vec2(force.x, force.y), true); break;
    }
}
void RigidBody::AddTorque(F32 torque, ForceMode mode)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    switch(mode)
    {
        case FORCE:   this->body->GetNativeBody()->ApplyTorque(torque, true); break;
        case IMPULSE: this->body->GetNativeBody()->ApplyAngularImpulse(torque, true); break;
    }
}

void RigidBody::Setup()
{
    switch(this->body->GetNativeBody()->GetType())
    {
        case b2_staticBody:    this->props.type = BodyType::STATIC; break;
        case b2_dynamicBody:   this->props.type = BodyType::DYNAMIC; break;
        case b2_kinematicBody: this->props.type = BodyType::KINEMATIC; break;
    }

    this->props.linearDrag = this->body->GetNativeBody()->GetLinearDamping();
    this->props.angularDrag = this->body->GetNativeBody()->GetAngularDamping();
    this->props.gravityScale = this->body->GetNativeBody()->GetGravityScale();

    this->props.fixedRotation = this->body->GetNativeBody()->IsFixedRotation();
    this->props.continuousCollison = this->body->GetNativeBody()->IsBullet();
}
void RigidBody::Update()
{
    b2Vec2 linearVelocity = this->body->GetNativeBody()->GetLinearVelocity();
    F32 angularVelocity = this->body->GetNativeBody()->GetAngularVelocity();

    linearVelocity *= PhysicsSystem::PTM_RATIO;
    angularVelocity *= PhysicsSystem::PTM_RATIO;

    this->props.linearVelocity = Vector3(linearVelocity.x, linearVelocity.y, 0.0f);
    this->props.angularVelocity = Vector3(angularVelocity, 0.0f, 0.0f);

    this->transform->position.x = this->body->GetNativeBody()->GetPosition().x * PhysicsSystem::PTM_RATIO;
    this->transform->position.y = this->body->GetNativeBody()->GetPosition().y * PhysicsSystem::PTM_RATIO;
    this->transform->rotation.z = this->body->GetNativeBody()->GetAngle();
}