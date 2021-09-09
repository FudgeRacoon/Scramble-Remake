#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <type_traits>

#include "Core/Common/Types.hpp"
#include "Core/Debug/Assert.hpp"
#include "Core/Logger/Logger.hpp"

#include "Scene/Component.hpp"
#include "Scene/Components/Tag.hpp"

namespace Scramble::Scene
{
    class Registry;

    class Entity
    {
    typedef std::vector<Component*> ComponentArray;

    private:
        ComponentArray components;
    
    public:
        U32 instanceId;
    private:
        Entity(U32 instanceId);

    private:
        ~Entity();

    public:
        template<typename CompT, typename... CompArgs>
        CompT* AddComponent(CompArgs... args)
        {
            SCRAMBLE_CORE_ASSERT_LOG((std::is_base_of<Component,CompT>::value), "Type passed is not a component!");
           
            for(auto component : this->components)
                if(dynamic_cast<CompT*>(component))
                    return dynamic_cast<CompT*>(component);
                
                    
            CompT* comp = new CompT(this, args...);
            components.push_back(comp);
            return comp;
        }
        template<typename CompT>
        CompT* GetComponent()
        {
            SCRAMBLE_CORE_ASSERT_LOG((std::is_base_of<Component,CompT>::value), "Type passed is not a component!");
            
            for(auto component : this->components)
            {
                CompT* qeuriedComponent = dynamic_cast<CompT*>(component);

                if(qeuriedComponent)
                    return qeuriedComponent;
            }

            return nullptr;
        }
        template<typename CompT>
        void RemoveComponent()
        {
           SCRAMBLE_CORE_ASSERT_LOG((std::is_base_of<Component,CompT>::value), "Type passed is not a component!");
        
            for(auto it = this->components.begin(); it != this->components.end(); it++)
                if(dynamic_cast<CompT*>(*it))
                {
                    delete *(it);
                    this->components.erase(it);
                    return;
                }
        }

    public:
        void Setup();
        void Update();
    
    friend Registry;
    };

    #define IsActive(value) GetComponent<Tag>()->enabled = value
}

#endif