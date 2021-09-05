#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdlib.h>

#include "GLFW/glfw3.h"

#include "WindowProps.hpp"
#include "Common/Types.hpp"
#include "Logger/Logger.hpp"

#include "../Input/KeyListener.hpp"
#include "../Input/MouseListener.hpp"

namespace Scramble
{
    class Window
    {
    public:
        typedef GLFWwindow NativeWindowHandle;
        typedef GLFWcursor NativeWindowCursor;
        
        typedef void(*WindowCloseCallback)(NativeWindowHandle*);
        typedef void(*WindowPosCallback)(NativeWindowHandle*, int, int);
        typedef void(*WindowResizeCallback)(NativeWindowHandle*, int, int);

        typedef void(*WindowKeyActionCallback)(NativeWindowHandle*, int, int, int, int);
        typedef void(*WindowMouseMotionCallback)(NativeWindowHandle*, double, double);
        typedef void(*WindowMouseActionCallback)(NativeWindowHandle*, int, int, int);
        typedef void(*WindowMouseScrollCallback)(NativeWindowHandle*, double, double);

    private:
        const char* title;
        U32 x, y;
        U32 width, height;
    
    private:
        NativeWindowHandle* windowHandle = nullptr;
        NativeWindowCursor* windowCursor = nullptr;
        U32 apiMajorVersion, apiMinorVersion;

    private:
        bool fullscreen;
        bool running;
        bool vSync;

    public:
        Window(const WindowProps& props = WindowProps());
        ~Window();

    private:
        void Init();
        void ShutDown();

    public:
        const char* GetTitle();
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
        void SetX(U32 value);
        void SetY(U32 value);
        void SetWidth(U32 value);
        void SetHeight(U32 value);

    public:
        void SetFullscreen(bool value);
        void SetVsync(bool value);
        void SetIcon();

    public:
        void SetOnWindowClose(WindowCloseCallback callbackFunc);
        void SetOnWindowPos(WindowPosCallback callbackFunc);
        void SetOnWindowResize(WindowResizeCallback callbackFunc);

    public:
        void SetOnKeyAction(WindowKeyActionCallback callbackFunc);
        void SetOnMouseMotion(WindowMouseMotionCallback callbackFunc);
        void SetOnMouseAction(WindowMouseActionCallback callbackFunc);
        void SetOnMouseScroll(WindowMouseScrollCallback callbackFunc);

    public:
        void PollEvents();
        void CloseWindow();
    };
}

#endif