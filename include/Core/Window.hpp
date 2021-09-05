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

    private:
        U32 x, y;
        U32 width, height;
    
    private:
        GLFWwindow* windowHandle = nullptr;

    private:
        bool fullscreen;
        bool running;
        bool vSync;

    public:
        Window(const WindowProps& props = WindowProps());

    public:
        ~Window();

    private:
        void Init();
        void ShutDown();

    public:
        const char* GetTitle();

    public:
        U32 GetX(); 
        U32 GetY();
        U32 GetWidth(); 
        U32 GetHeight();

    public:
        NativeWindowHandle* GetNativeHandle();

    public:
        bool IsFullscreen();
        bool IsRunning();
        bool IsVsync();

    public:
        void SetTitle(const char* title);
    
    public:
        void SetX(U32 value); 
        void SetY(U32 value);
        void SetWidth(U32 value); 
        void SetHeight(U32 value);

    public:
        void SetFullscreen(bool value);
        void SetVsync(bool value);
    
    public:
        void CloseWindow();
    };
}

#endif