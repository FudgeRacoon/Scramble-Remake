#include "Input/InputManager.hpp"
using namespace Scramble::Input;

#include <stdio.h>

const byte* InputManager::keyboardState = nullptr;
byte* InputManager::prevKeyboardState = nullptr;

const byte* InputManager::mouseState = nullptr;
byte* InputManager::prevMouseState = nullptr;

I32* InputManager::mousePosX = nullptr;
I32* InputManager::mousePosY = nullptr;
I32* InputManager::mouseOffsetX = nullptr;
I32* InputManager::mouseOffsetY = nullptr;

I32 InputManager::prevMousePosX; 
I32 InputManager::prevMousePosY;

void InputManager::OnStartUp()
{
    S_INFO("InputManager is starting up...");

    keyboardState = KeyListener::GetInstance()->GetKeyboardState();
    prevKeyboardState = new byte[512];

    mouseState = MouseListener::GetInstance()->GetMouseState(
        mousePosX, 
        mousePosY, 
        mouseOffsetX, 
        mouseOffsetY
    );
    prevMouseState = new byte[8];
}
void InputManager::OnFrameEnd()
{
    memcpy(prevKeyboardState, keyboardState, 512);
    memcpy(prevMouseState, mouseState, 8);

    prevMousePosX = *mousePosX;
    prevMousePosY = *mousePosY;
}

bool InputManager::GetKey(KeyCode code)
{
    return keyboardState[code];
}
bool InputManager::GetKeyDown(KeyCode code)
{
    return !prevKeyboardState[code] && keyboardState[code];
}
bool InputManager::GetKeyUp(KeyCode code)
{
    return prevKeyboardState[code] && !keyboardState[code];
}
bool InputManager::GetMouseButton(MouseCode button)
{
    return mouseState[button];
}
bool InputManager::GetMouseButtonDown(MouseCode button)
{
    return !prevMouseState[button] && mouseState[button];
}
bool InputManager::GetMouseButtonUp(MouseCode button)
{
    return prevMouseState[button] && !mouseState[button];
}
I32 InputManager::GetMouseScrollDelta()
{
    return *mouseOffsetY;
}