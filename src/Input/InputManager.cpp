#include "Input/InputManager.hpp"
using namespace Scramble::Input;

#include <stdio.h>

const byte* InputManager::keyboardState = nullptr;
byte* InputManager::prevKeyboardState = nullptr;
I32 InputManager::keyboardStateLength = 0;

const byte* InputManager::mouseState = nullptr;
byte* InputManager::prevMouseState = nullptr;
I32 InputManager::mouseStateLength = 0;

I32* InputManager::mousePosX = nullptr;
I32* InputManager::mousePosY = nullptr;
I32* InputManager::prevMousePosX = nullptr; 
I32* InputManager::prevMousePosY = nullptr;
I32* InputManager::mouseOffsetX = nullptr;
I32* InputManager::mouseOffsetY = nullptr;

void InputManager::OnStartUp()
{
    keyboardState = KeyListener::GetKeyboardState(&keyboardStateLength);
    prevKeyboardState = new byte[keyboardStateLength];

    mouseState = MouseListener::GetMouseState(
        mousePosX, 
        mousePosY, 
        mouseOffsetX, 
        mouseOffsetY, 
        &mouseStateLength
    );
    prevMouseState = new byte[mouseStateLength];
}
void InputManager::OnFrameEnd()
{
    memcpy(prevKeyboardState, keyboardState, keyboardStateLength);
    memcpy(prevMouseState, mouseState, mouseStateLength);

    prevMousePosX = mousePosX;
    prevMousePosY = mousePosY;
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