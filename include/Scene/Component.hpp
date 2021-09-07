#ifndef COMPONENT_HPP
#define COMPONENT_HPP

namespace Scramble::Scene
{
    class Entity;

    class Component
    {
    public:
        Entity* owner;

    protected:
        Component(Entity* owner);

    protected:
        virtual ~Component();

    public:
        virtual void Setup() = 0;
        virtual void Update() = 0;

    friend Entity;
    };
}

#endif