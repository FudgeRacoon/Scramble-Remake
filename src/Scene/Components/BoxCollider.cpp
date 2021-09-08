#include "Scene/Components/BoxCollider.hpp"
using namespace Scramble::Scene;

#include "Scene/Components/RigidBody.hpp"

#include "Core/Math/Color.hpp"
#include "Graphics/Renderer.hpp"

BoxCollider::BoxCollider(Entity* owner) : Component(owner)
{
    this->ownerTransform = this->owner->GetComponent<Transform>();

    this->props.bounds.SetSize(Vector3(64.0, 64.0, 0.0));
    
    this->props.friction = 0.1;
    this->props.resistution = 0.0;

    this->props.isTrigger = false;

    RigidBody* rigidbody = owner->GetComponent<RigidBody>();
    
    if(!rigidbody)
    {
        owner->AddComponent<RigidBody>();
        rigidbody = owner->GetComponent<RigidBody>();
    }
        
    PhysicsSystem::AddBoxCollider(rigidbody, this);
}
BoxCollider::BoxCollider(Entity* owner, Vector3 size) : Component(owner)
{
    this->ownerTransform = this->owner->GetComponent<Transform>();

    this->props.bounds.SetSize(size);
    
    this->props.friction = 0.1;
    this->props.resistution = 0.0;

    this->props.isTrigger = false;

    RigidBody* rigidbody = owner->GetComponent<RigidBody>();
    
    if(!rigidbody)
    {
        owner->AddComponent<RigidBody>();
        rigidbody = owner->GetComponent<RigidBody>();
    }
        
    PhysicsSystem::AddBoxCollider(rigidbody, this);
}

Vector3 BoxCollider::GetSize()
{
    return this->props.bounds.GetSize();
}
Vector3 BoxCollider::GetCenter()
{
    return this->props.bounds.GetCenter();
}
Vector3 BoxCollider::GetExtents()
{
    return this->props.bounds.GetExtents();
}

F32 BoxCollider::GetFriction()
{
    return this->props.friction;
}
F32 BoxCollider::GetResistution()
{
    return this->props.resistution;
}

bool BoxCollider::IsTrigger()
{
    return this->props.isTrigger;
}

void BoxCollider::SetSize(Vector3 value)
{
    this->props.bounds.SetSize(value);

    PhysicsSystem::ResetBoxCollider(owner->GetComponent<RigidBody>(), this);
}
void BoxCollider::SetCenter(Vector3 value)
{
    this->props.bounds.SetCenter(value);
    this->props.offset = value - ownerTransform->position;

    PhysicsSystem::ResetBoxCollider(owner->GetComponent<RigidBody>(), this);
}
void BoxCollider::SetExtents(Vector3 value)
{
    this->props.bounds.SetExtents(value);
    
    PhysicsSystem::ResetBoxCollider(owner->GetComponent<RigidBody>(), this);
}

void BoxCollider::SetFriction(F32 value)
{
    this->props.friction = value;

    PhysicsSystem::ResetBoxCollider(owner->GetComponent<RigidBody>(), this);
}
void BoxCollider::SetResistution(F32 value)
{
    this->props.resistution = value;

    PhysicsSystem::ResetBoxCollider(owner->GetComponent<RigidBody>(), this);
}

void BoxCollider::SetTrigger(bool value)
{
    this->props.isTrigger = value;

    PhysicsSystem::SetSensor(owner->GetComponent<RigidBody>(), value);
}

void BoxCollider::Setup() {}
void BoxCollider::Update()
{
    this->props.bounds.SetCenter(this->ownerTransform->position + this->props.offset);

    Renderer::DrawQuad(
        Rect(
            this->props.bounds.GetMin().x,
            this->props.bounds.GetMin().y + this->props.bounds.GetSize().y,
            this->props.bounds.GetSize().x,
            this->props.bounds.GetSize().y
        ),
        Color::red
    );
}