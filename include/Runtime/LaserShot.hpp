#ifndef LASER_SHOT_HPP
#define LASER_SHOT_HPP

#include "Scramble.hpp"
using namespace Scramble::Graphics;
using namespace Scramble::Input;
using namespace Scramble::Scene;
using namespace Scramble::Utils;

class LaserShot : public Component
{
private:
    Transform* transform;
    RigidBody* rigidbody;
    BoxCollider* collider;
    SpriteRenderer* spriteRenderer;

private:
    void SetSprite()
    {
        spriteRenderer->sprite = ResourceManager::GetSprite("LaserShot");
    }
    void SetDimensions()
    {
        transform->scale = Vector3(0.03f, 0.03f, 1.0);
    }
    void SetPhysicsAtrributes()
    {
        rigidbody->SetLinearDrag(1.0f);
        rigidbody->SetLinearVelocity(Vector3(300.0f, 0.0f, 0.0f));
    
        collider->SetTrigger(true);
    }

public:
    LaserShot(Entity* entity, Vector3 position) : Component(entity)
    {
        owner->GetComponent<Transform>()->position = position;
    }

public:
    void Setup() override
    {
        transform = owner->GetComponent<Transform>();
        rigidbody = owner->AddComponent<RigidBody>(BodyType::KINEMATIC);
        collider = owner->AddComponent<BoxCollider>(Vector3(2.0f, 2.0f, 0.0f));
        spriteRenderer = owner->AddComponent<SpriteRenderer>();
        
        SetSprite();
        SetDimensions();
        SetPhysicsAtrributes();
    }
    void Update() override
    {
        if(transform->position.x > 224.0f || transform->position.x < -224.0f)
            DestroyEntityById(owner->instanceId);
    }

};

#endif