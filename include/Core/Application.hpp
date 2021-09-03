#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include "Scramble.hpp"

namespace Scramble
{
    class Application
    {
    private:
        static std::unique_ptr<Window> windowContext;
        static std::unique_ptr<RuntimeInstance> runtimeContext;
    
    public:
        static void Start(RuntimeInstance* instance);
        static void Run();
        static void ShutDown();
    };
}

#endif