#ifndef KEYLISTENER_HPP
#define KEYLISTENER_HPP

#include <string.h>

#include "GLFW/glfw3.h"

#include "Core/Common/Types.hpp"

namespace Scramble::Input
{
    class KeyListener
    {
    private:
        static byte* keyboardStates;

    private:
        KeyListener() = delete;
        ~KeyListener() = delete;    

    public:
        static void OnStartUp();
        static void OnShutDown();

    public:
        static const byte* GetKeyboardState(I32* length = nullptr);

    public:
        static void KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);
    };
}

#endif