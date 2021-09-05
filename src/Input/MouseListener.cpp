#include "Input/MouseListener.hpp"
using namespace Scramble::Input;

I32* MouseListener::x = nullptr;
I32* MouseListener::y = nullptr;
I32* MouseListener::xOffset = nullptr;
I32* MouseListener::yOffset = nullptr;
byte* MouseListener::mouseState = nullptr;

void MouseListener::OnStartUp()
{
    S_INFO("MouseListener is starting up...");

    MouseListener::x = new I32(0); 
    MouseListener::y = new I32(0);
    MouseListener::xOffset = new I32(0); 
    MouseListener::yOffset = new I32(0);
    MouseListener::mouseState = new byte[8];
    memset(MouseListener::mouseState, 0, 8);
}
void MouseListener::OnShutDown()
{
    delete MouseListener::x; 
    delete MouseListener::y;
    delete MouseListener::xOffset; 
    delete MouseListener::yOffset;
    delete[] MouseListener::mouseState;
}

const byte* MouseListener::GetMouseState(I32*& x, I32*& y, I32*& xOffset, I32*& yOffset)
{
    x = MouseListener::x; 
    y = MouseListener::y;
    xOffset = MouseListener::xOffset; 
    yOffset = MouseListener::yOffset;

    return MouseListener::mouseState;
}

void MouseListener::MousePosCallback(GLFWwindow* handle, double x, double y)
{
    *MouseListener::x = static_cast<int>(x);
    *MouseListener::y = static_cast<int>(y);
}
void MouseListener::MouseButtonCallback(GLFWwindow* handle, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
        mouseState[button] = 1;
    else if(action == GLFW_RELEASE)
        mouseState[button] = 0;
}
void MouseListener::MouseScrollCallback(GLFWwindow* handle, double xOffset, double yOffset)
{
    *MouseListener::xOffset = static_cast<int>(xOffset);
    *MouseListener::yOffset = static_cast<int>(yOffset);
}