#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <string>
#include <queue>
#include <unordered_map>

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"
#include "Core/Math/Vector3.hpp"

#include "Components/Tag.hpp"
#include "Components/Transform.hpp"
#include "Entity.hpp"

namespace Scramble::Scene
{
    struct EntityIdGenerator
    {
        U32 counter = 0;
        U32 operator ()() {return counter++;}
    };

    class Registry
    {
    typedef std::unordered_map<U32, SharedPtr<Entity>> EntityMap;
    typedef std::queue<SharedPtr<Entity>> EntitySetupQueue;
    typedef std::queue<SharedPtr<Entity>> EntityDestroyQueue;

    typedef void(*CallbackFunc)(SharedPtr<Entity>);

    private:
        EntityMap entites;
        EntitySetupQueue setupQueue;
        EntityDestroyQueue destroyQueue;

    private:
        EntityIdGenerator IdGenerator;
    
    public:
        Registry() = default;

    public:
        void ForEach(CallbackFunc func);

    public:
        EntityMap GetEntities();

    public:
        WeakPtr<Entity> AddEntity();
        WeakPtr<Entity> AddEntity(std::string tag, bool enabled = true);
        WeakPtr<Entity> AddEntity(Vector3 position, Vector3 rotation, Vector3 scale);
        WeakPtr<Entity> AddEntity(std::string tag, Vector3 position, Vector3 rotation, Vector3 scale);

    public:
        WeakPtr<Entity> GetEntityById(U32 id);
        WeakPtr<Entity> GetEntityByTag(std::string tag);

    public:
        void DestroyEntityById(U32 id);
        void DestroyEntityByTag(std::string tag);

    public:
        void PollSetupQueue();
        void ResetSetupQueue();
        void PollDestroyQueue();
    
    public:
        void Release();
    };     
}

#endif