#include "Scene/Components/BoxCollider.hpp"
using namespace Scramble::Scene;

#include "Core/Math/Color.hpp"
#include "Graphics/Renderer.hpp"

BoxCollider::BoxCollider(Entity* owner) : Component(owner)
{
    this->ownerTransform = this->owner->GetComponent<Transform>();

    this->props.bounds.SetSize(Vector3(64.0, 64.0, 0.0));

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
    return this->bounds.GetSize();
}
Vector3 BoxCollider::GetCenter()
{
    return this->bounds.GetCenter();
}
Vector3 BoxCollider::GetExtents()
{
    return this->bounds.GetExtents();
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
    this->props.bounds.SetCenter(this->ownerTransform->position + this->offset);

    Renderer::DrawQuad(
        Rect(
            this->props.bounds.GetMin().x,
            this->props.bounds.GetMin().y + bounds.GetSize().y,
            this->props.bounds.GetSize().x,
            this->props.bounds.GetSize().y
        ),
        Color::red
    );
}