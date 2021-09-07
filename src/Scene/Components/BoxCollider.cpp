#include "Scene/Components/BoxCollider.hpp"
using namespace Scramble::Scene;

BoxCollider::BoxCollider()
{
    this->ownerTransform = this->owner->GetComponent<Transform>();
    this->ownerSpriteRenderer = this->owner->GetComponent<SpriteRenderer>();

    if(ownerSpriteRenderer)
    {
        WeakPtr<Sprite> sprite = this->ownerSpriteRenderer->sprite;
        if(!sprite.expired())
        {
            this->bounds.SetSize(Vector3(sprite.lock()->GetWidth(), sprite.lock()->GetHeight(), 0.0));
            return;
        }
    }

    this->bounds.SetSize(Vector3(32.0, 32.0, 0.0));
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

    Vector3 center = this->bounds.GetCenter();
    Vector3 extents = this->bounds.GetExtents();
    this->nativeShape->SetAsBox(extents.x, extents.y, b2Vec2(center.x, center.y), 0.0);
}
void BoxCollider::SetCenter(Vector3 value)
{
    this->bounds.SetCenter(value);
    this->offset = this->ownerTransform->position - value;

    Vector3 extents = this->bounds.GetExtents();
    this->nativeShape->SetAsBox(extents.x, extents.y, b2Vec2(value.x, value.y), 0.0);
}
void BoxCollider::SetExtents(Vector3 value)
{
    this->bounds.SetExtents(value);
    
    Vector3 center = this->bounds.GetCenter();
    this->nativeShape->SetAsBox(value.x, value.y, b2Vec2(center.x, center.y), 0.0);
}

void BoxCollider::Setup()
{
    
} 
void BoxCollider::Update()
{
    this->bounds.SetCenter(this->ownerTransform->position + this->offset);
}