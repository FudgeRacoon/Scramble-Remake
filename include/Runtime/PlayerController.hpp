#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "Scramble.hpp"
using namespace Scramble::Graphics;
using namespace Scramble::Input;
using namespace Scramble::Scene;
using namespace Scramble::Utils;

class PlayerController : public Component
{
private:
    F32 movementForce;
    F32 maximumVelocity;

private:
    bool clampVelX = false;
    bool clampVelY = false;

private:
    RigidBody* rigidbody;

private:
    void Move(Vector3 direction)
    {
        rigidbody->AddForce(direction * movementForce * Time::GetDeltaTime(), ForceMode::IMPULSE);

        Vector3 velocity = rigidbody->GetLinearVelocity();
        
        if(Math::Abs(velocity.x) > maximumVelocity)
        {
            clampVelX = true;
            velocity.x = velocity.x > 0 ? maximumVelocity : -(maximumVelocity);
        }

        if(Math::Abs(velocity.y) > maximumVelocity)
        {
            clampVelY = true;
            velocity.y = velocity.y > 0 ? maximumVelocity : -(maximumVelocity);
        }
        
        if(clampVelX || clampVelY)
        {
            clampVelX = false;
            clampVelY = false;
            rigidbody->SetLinearVelocity(velocity);
        }
    }

public:
    PlayerController(Entity* entity) : Component(entity) {}

public:
    void Setup() override
    {
        movementForce = 5.0f;
        maximumVelocity = 200.0f;

        rigidbody = owner->GetComponent<RigidBody>();

        rigidbody->SetLinearDrag(0.3f);
        rigidbody->SetGravityScale(0.0f);
        rigidbody->SetFixedRotation(true);
    }
    void Update() override
    {
        if(InputManager::GetKey(KeyCode::KEY_D))
            Move(Vector3::Right);
        if(InputManager::GetKey(KeyCode::KEY_A))
            Move(Vector3::Left);
        if(InputManager::GetKey(KeyCode::KEY_W))
            Move(Vector3::Up);
        if(InputManager::GetKey(KeyCode::KEY_S))
            Move(Vector3::Down);
    }
};  

#endif