#include "Scene/Components/RigidBody.hpp"
using namespace Scramble::Scene;

#include "Scene/Entity.hpp"

RigidBody::RigidBody()
{
    this->rawBody = nullptr;

    this->bodyType = BodyType::DYNAMIC;

    this->mass = 10.0;
    this->linearDrag = 0.5f;
    this->angularDrag = 0.5f;

    this->fixedRotation = false;
    this->continuousCollison = true;
}
RigidBody::RigidBody(BodyType bodyType, F32 mass)
{
    this->rawBody = nullptr;

    this->bodyType = bodyType;

    this->mass = mass;
    this->linearDrag = 0.5f;
    this->angularDrag = 0.5f;

    this->fixedRotation = false;
    this->continuousCollison = true;
}

void RigidBody::Setup()
{
    this->ownerTransform = owner->GetComponent<Transform>();
}
void RigidBody::Update()
{
    this->ownerTransform->position.x = this->rawBody->GetPosition().x;
    this->ownerTransform->position.y = this->rawBody->GetPosition().y;
    this->ownerTransform->rotation.z = this->rawBody->GetAngle();
}