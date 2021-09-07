#include "Scene/Components/BoxCollider.hpp"
using namespace Scramble::Scene;

#include "Core/Math/Color.hpp"
#include "Graphics/Renderer.hpp"
#include "Core/Logger/Logger.hpp"

BoxCollider::BoxCollider(Entity* owner) : Component(owner)
{
    this->ownerTransform = this->owner->GetComponent<Transform>();
    
    this->bounds.SetSize(Vector3(64.0, 64.0, 0.0));
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

void BoxCollider::SetSize(Vector3 value)
{
    this->bounds.SetSize(value);

    Vector3 center = this->bounds.GetCenter() / PhysicsSystem::PPM;
    Vector3 extents = this->bounds.GetExtents() / PhysicsSystem::PPM;
    this->nativeShape->SetAsBox(extents.x, extents.y, b2Vec2(center.x, center.y), 0.0);
}
void BoxCollider::SetCenter(Vector3 value)
{
    this->bounds.SetCenter(value);
    this->offset = this->ownerTransform->position - value;

    value = value / PhysicsSystem::PPM;

    Vector3 extents = this->bounds.GetExtents() / PhysicsSystem::PPM;
    this->nativeShape->SetAsBox(extents.x, extents.y, b2Vec2(value.x, value.y), 0.0);
}
void BoxCollider::SetExtents(Vector3 value)
{
    this->bounds.SetExtents(value);
    
    value = value  / PhysicsSystem::PPM;

    Vector3 center = this->bounds.GetCenter() / PhysicsSystem::PPM;;
    this->nativeShape->SetAsBox(value.x, value.y, b2Vec2(center.x, center.y), 0.0);
}

void BoxCollider::Setup()
{
   
} 
void BoxCollider::Update()
{
    this->bounds.SetCenter(this->ownerTransform->position + this->offset);

    Renderer::DrawQuad(
        Rect(
            bounds.GetMin().x,
            bounds.GetMin().y + bounds.GetSize().y,
            bounds.GetSize().x,
            bounds.GetSize().y
        ),
        Color::red
    );
}