#include "Scene/Registry.hpp"
using namespace Scramble::Scene;

void Registry::ForEach(Registry::CallbackFunc func)
{
    for(auto entity : this->entites)
        func(entity.second);
}

Registry::EntityMap Registry::GetEntities()
{
    return this->entites;
}

WeakPtr<Entity> Registry::AddEntity()
{
    U32 instanceId = IdGenerator();
    
    std::string tag = "Entity_" + std::to_string(instanceId);

    SharedPtr<Entity> entity(new Entity(instanceId), [] (Entity* entity) {delete entity;});
    entity->AddComponent<Tag>(tag);
    entity->AddComponent<Transform>(Vector3(), Vector3(), Vector3(1.0, 1.0, 1.0));

    entites.insert(
        std::make_pair(instanceId, entity)
    );

    setupQueue.push(entity);
    
    S_INFO("Entity: %s has been created succesfully!", tag.c_str());

    return entity;
}
WeakPtr<Entity> Registry::AddEntity(std::string tag)
{
    U32 instanceId = IdGenerator();
    
    SharedPtr<Entity> entity(new Entity(instanceId), [] (Entity* entity) {delete entity;});
    entity->AddComponent<Tag>(tag);
    entity->AddComponent<Transform>(Vector3(), Vector3(), Vector3(1.0, 1.0, 1.0));

    entites.insert(
        std::make_pair(instanceId, entity)
    );

    setupQueue.push(entity);

    S_INFO("Entity: %s has been created succesfully!", tag.c_str());

    return entity;
}
WeakPtr<Entity> Registry::AddEntity(Vector3 position, Vector3 rotation, Vector3 scale)
{
    U32 instanceId = IdGenerator();
    
    std::string tag = "Entity_" + std::to_string(instanceId);

    SharedPtr<Entity> entity(new Entity(instanceId), [] (Entity* entity) {delete entity;});
    entity->AddComponent<Tag>(tag);
    entity->AddComponent<Transform>(position, rotation, scale);

    entites.insert(
        std::make_pair(instanceId, entity)
    );

    setupQueue.push(entity);

    S_INFO("Entity: %s has been created succesfully!", tag.c_str());

    return entity;
}   
WeakPtr<Entity> Registry::AddEntity(std::string tag, Vector3 position, Vector3 rotation, Vector3 scale)
{
    U32 instanceId = IdGenerator();
    
    SharedPtr<Entity> entity(new Entity(instanceId), [] (Entity* entity) {delete entity;});
    entity->AddComponent<Tag>(tag);
    entity->AddComponent<Transform>(position, rotation, scale);

    entites.insert(
        std::make_pair(instanceId, entity)
    );

    setupQueue.push(entity);

    S_INFO("Entity: %s has been created succesfully!", tag.c_str());

    return entity;
}

WeakPtr<Entity> Registry::GetEntityById(U32 id)
{
    auto it = entites.find(id);

    if(it != entites.end())
        return it->second;

    S_WARN("Entity does not exist!");
}
WeakPtr<Entity> Registry::GetEntityByTag(std::string tag)
{
    auto it = entites.begin();

    for( ; it != entites.end(); it++)
        if(it->second->GetComponent<Tag>()->tag == tag)
            return it->second;

    S_WARN("Entity does not exist!");
}

void Registry::DestroyEntityById(U32 id)
{
    auto it = entites.find(id);

    if(it != entites.end())
    {
        destroyQueue.push(it->second);

        it->second.reset();
        entites.erase(it);

        S_INFO("Entity: %s has been destroyed succesfully!", it->second->GetComponent<Tag>()->tag.c_str());
    }

    S_WARN("Entity does not exist!");
}
void Registry::DestroyEntityByTag(std::string tag)
{
    auto it = entites.begin();

    for( ; it != entites.end(); it++)
        if(it->second->GetComponent<Tag>()->tag == tag)
        {
            destroyQueue.push(it->second);

            it->second.reset();
            entites.erase(it);

            S_INFO("Entity: %s has been destroyed succesfully!", tag.c_str());

            return;
        }

    S_WARN("Entity does not exist!");
}

void Registry::PollSetupQueue()
{
    while(!setupQueue.empty())
    {
        setupQueue.front()->Setup();
        setupQueue.pop();
    }
}
void Registry::PollDestroyQueue()
{
    while(!destroyQueue.empty())
    {
        destroyQueue.front().reset();
        destroyQueue.pop();
    }
}

void Registry::Release()
{
    for(auto entity : entites)
        entity.second.reset();

    entites.clear();

    while(!setupQueue.empty())
    {
        setupQueue.front().reset();
        setupQueue.pop();
    }

    while(!destroyQueue.empty())
    {
        destroyQueue.front().reset();
        destroyQueue.pop();
    }
}
void Registry::ResetSetupQueue()
{
    for(auto entity : entites)
        setupQueue.push(entity.second);
}

