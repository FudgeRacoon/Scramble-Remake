#ifndef MOUSELISTENER_HPP
#define MOUSELISTENER_HPP

#include <string.h>

#include "GLFW/glfw3.h"

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"

namespace Scramble::Input
{
    class MouseListener
    {
    private:
        static I32* x; 
        static I32* y;
        static I32* xOffset; 
        static I32* yOffset;
        static byte* mouseState;

    private:
        MouseListener() = delete;
        ~MouseListener() = delete;

    public:
        static void OnStartUp();
        static void OnShutDown();

    public:
        static const byte* GetMouseState(I32*& x, I32*& y, I32*& xOffset, I32*& yOffset);

    public:
        static void MousePosCallback(GLFWwindow* handle, double x, double y);
        static void MouseButtonCallback(GLFWwindow* handle, int button, int action, int mods);
        static void MouseScrollCallback(GLFWwindow* handle, double xOffset, double yOffset);
    };
}

#endif