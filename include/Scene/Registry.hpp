#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <string>
#include <queue>
#include <unordered_map>

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"
#include "Core/Math/Vector3.hpp"

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
    typedef std::unordered_map<U32, Entity*> EntityMap;
    typedef std::queue<Entity*> EntitySetupQueue;
    typedef std::queue<Entity*> EntityDestroyQueue;

    private:
        EntityMap entites;
        EntitySetupQueue setupQueue;
        EntityDestroyQueue destroyQueue;

    private:
        EntityIdGenerator IdGenerator;
    
    public:
        Entity* AddEntity();
        Entity* AddEntity(std::string tag);
        Entity* AddEntity(Vector3 position, Vector3 rotation, Vector3 scale);
        Entity* AddEntity(std::string tag, Vector3 position, Vector3 rotation, Vector3 scale);

    public:
        Entity* GetEntityById(U32 id);
        Entity* GetEntityByTag(std::string tag);

    public:
        void DestroyEntityById(U32 id);
        void DestroyEntityByTag(std::string tag);

    public:
        void PollSetupQueue();
        void PollDestroyQueue();

    public:
        void Release();
    };
}

#endif