#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <string.h>

#include "Core/Common/Types.hpp"

#include "KeyCodes.hpp"
#include "MouseCodes.hpp"
#include "KeyListener.hpp"
#include "MouseListener.hpp"

namespace Scramble::Input
{
    class InputManager
    {
    private:
        static const byte* keyboardState;
        static byte* prevKeyboardState;

    private:
        static const byte* mouseState;
        static byte* prevMouseState;

    private:
        static I32* mousePosX; 
        static I32* mousePosY;
        static I32* mouseOffsetX; 
        static I32* mouseOffsetY;

    private:
        static I32 prevMousePosX; 
        static I32 prevMousePosY;
    
    private:
        InputManager() = delete;
        ~InputManager() = delete;

    public:
        static void OnStartUp();
        static void OnFrameEnd();

    public:
        static bool GetKey(KeyCode code);
        static bool GetKeyDown(KeyCode code);
        static bool GetKeyUp(KeyCode code);
        static bool GetMouseButton(MouseCode button);
        static bool GetMouseButtonDown(MouseCode button);
        static bool GetMouseButtonUp(MouseCode button);
        static I32 GetMouseScrollDelta();
    };
}

#endif