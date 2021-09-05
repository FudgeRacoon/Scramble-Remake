#include "Input/KeyListener.hpp"
using namespace Scramble::Input;

byte* KeyListener::keyboardStates = nullptr;

void KeyListener::OnStartUp()
{
    S_INFO("KeyListener is starting up...");

    keyboardStates = new byte[512];
    memset(keyboardStates, 0, 512);
}
void KeyListener::OnShutDown()
{
    delete[] keyboardStates;
}

const byte* KeyListener::GetKeyboardState()
{
    return keyboardStates;
}

void KeyListener::KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        keyboardStates[key] = 1;
    else if(action == GLFW_RELEASE)
        keyboardStates[key] = 0;
}

