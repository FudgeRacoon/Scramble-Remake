#ifndef RUNTIME_INSTANCE_HPP
#define RUNTIME_INSTANCE_HPP

namespace Scramble
{
    class RuntimeInstance
    {
    public:
        virtual void OnEnter() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnExit() = 0;
    };
}

#endif