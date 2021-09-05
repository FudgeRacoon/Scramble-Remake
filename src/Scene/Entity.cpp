#include "Scene/Entity.hpp"
using namespace Scramble::Scene;

Entity::Entity(U32 instanceId)
    :instanceId(instanceId) {}

Entity::~Entity()
{
    for(auto component : this->components)
        delete component;

    this->components.clear();
}

void Entity::Setup()
{
    for(auto component : this->components)
        component->Setup();
}
void Entity::Update()
{
    for(auto component : this->components)
        component->Update();
}