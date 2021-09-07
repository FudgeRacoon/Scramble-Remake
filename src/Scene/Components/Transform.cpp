#include "Scene/Components/Transform.hpp"
using namespace Scramble::Scene;

Transform::Transform(Entity* owner) : Component(owner) {}
Transform::Transform(Entity* owner, Vector3 position, Vector3 rotation, Vector3 scale) : Component(owner)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

void Transform::Setup() {}
void Transform::Update() {}