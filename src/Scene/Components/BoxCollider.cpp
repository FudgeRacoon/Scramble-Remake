#include "Scene/Components/BoxCollider.hpp"
using namespace Scramble::Scene;

#include "Scene/Components/RigidBody.hpp"

#include "Core/Math/Color.hpp"
#include "Graphics/Renderer.hpp"

BoxCollider::BoxCollider(Entity* owner) : Component(owner)
{
    this->transform = owner->GetComponent<Transform>();
    RigidBody* rigidbody = owner->AddComponent<RigidBody>();
    
    this->props.bounds.SetSize(Vector3(32.0, 32.0, 0.0));

    this->body = rigidbody->GetBody();
    this->body->AddBoxFixture(this->props.bounds);
}
BoxCollider::BoxCollider(Entity* owner, Vector3 size) : Component(owner)
{
    this->transform = owner->GetComponent<Transform>();
    RigidBody* rigidbody = owner->AddComponent<RigidBody>();
    
    this->props.bounds.SetSize(size);

    this->body = rigidbody->GetBody();
    this->body->AddBoxFixture(this->props.bounds);
}

Vector3 BoxCollider::GetSize()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.bounds.GetSize();
}
Vector3 BoxCollider::GetCenter()
{   
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.bounds.GetCenter();
}
Vector3 BoxCollider::GetExtents()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.bounds.GetExtents();
}

F32 BoxCollider::GetMass()
{   
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.mass;
}
F32 BoxCollider::GetFriction()
{   
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.friction;
}
F32 BoxCollider::GetResistution()
{   
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.resistution;
}

bool BoxCollider::IsTrigger()
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    return this->props.isTrigger;
}

void BoxCollider::SetSize(Vector3 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.bounds.SetSize(value);

    this->body->ResetFixture();
    this->body->AddBoxFixture(
        this->props.bounds,
        this->props.mass,
        this->props.friction,
        this->props.resistution,
        this->props.isTrigger
    );
}
void BoxCollider::SetCenter(Vector3 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.bounds.SetCenter(value);
    this->props.offset = value - transform->position;

    this->body->ResetFixture();
    this->body->AddBoxFixture(
        this->props.bounds,
        this->props.mass,
        this->props.friction,
        this->props.resistution,
        this->props.isTrigger
    );
}
void BoxCollider::SetExtents(Vector3 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");
    
    this->props.bounds.SetExtents(value);
    
    this->body->ResetFixture();
    this->body->AddBoxFixture(
        this->props.bounds,
        this->props.mass,
        this->props.friction,
        this->props.resistution,
        this->props.isTrigger
    );
}

void BoxCollider::SetMass(F32 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.mass = value;

    //[TODO] set mass
}
void BoxCollider::SetFriction(F32 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.friction = value;

    this->body->GetNativeFixture()->SetFriction(value);
}
void BoxCollider::SetResistution(F32 value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.resistution = value;

    this->body->GetNativeFixture()->SetRestitution(value);
}

void BoxCollider::SetTrigger(bool value)
{
    SCRAMBLE_CORE_ASSERT_LOG(this, "Component is null!");

    this->props.isTrigger = value;

    this->body->GetNativeFixture()->SetSensor(value);
}

void BoxCollider::Setup()
{
    this->props.friction = this->body->GetNativeFixture()->GetFriction();
    this->props.resistution = this->body->GetNativeFixture()->GetRestitution();

    this->props.isTrigger = this->body->GetNativeFixture()->IsSensor();
}
void BoxCollider::Update()
{
    this->props.bounds.SetCenter(this->transform->position + this->props.offset);

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