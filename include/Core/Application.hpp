#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Common/Types.hpp"

#include "Graphics/OpenGL/Debug/OpenGLDebugger.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/Renderer.hpp"

#include "Time/Time.hpp"
#include "Time/Timer.hpp"
#include "RuntimeInstance.hpp"
#include "Window.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Events/Event.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/EventHandler.hpp"

#include "Input/InputManager.hpp"
#include "Input/KeyListener.hpp"
#include "Input/MouseListener.hpp"

namespace Scramble
{
    class Application
    {
    private:
        static UniquePtr<Window> windowContext;
        static UniquePtr<RuntimeInstance> runtimeContext;
    
    public:
        static void Start(RuntimeInstance* instance);
        static void Run();
        static void ShutDown();
    };
}

#endif