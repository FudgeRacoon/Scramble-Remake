#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdlib.h>

#include "GLFW/glfw3.h"

#include "WindowProps.hpp"
#include "Common/Types.hpp"
#include "Logger/Logger.hpp"

#include "../Events/EventHandler.hpp"
using namespace Scramble::Events;

namespace Scramble
{
    class Window : public EventHandler
    {
    public:
        typedef GLFWwindow NativeWindowHandle;
    
    private:
        const char* title;
        NativeWindowHandle* windowHandle;
    
    private:
        bool vSync;
        bool running;
        bool fullscreen;
    
    public:
        U32 x, y;
        U32 width, height;
    
    public:
        Window(const WindowProps& props = WindowProps());

    public:
        ~Window();

    private:
        void Internal_Init();
        void Internal_ShutDown();
        void Internal_CreateWindow();

    public:
        const char* GetTitle();
        NativeWindowHandle* GetNativeHandle();
 
    public:
        bool IsVsync();
        bool IsRunning();
        bool IsFullscreen();

    public:
        void SetTitle(const char* title);

    public:
        void SetVsync(bool value);
        void SetFullscreen(bool value);

    public:
        void CloseWindow();
    };
}

#endif