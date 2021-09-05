#ifndef KEYLISTENER_HPP
#define KEYLISTENER_HPP

#include <string.h>

#include "GLFW/glfw3.h"

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"

#include "Events/KeyEvent.hpp"
#include "Events/EventHandler.hpp"
using namespace Scramble::Events;

namespace Scramble::Input
{
    class KeyListener : public EventHandler
    {
    private:
        byte* keyboardStates; 

    private:
        KeyListener();

    public:
        ~KeyListener();

    public:
        static KeyListener* GetInstance();

    public:
        const byte* GetKeyboardState();
    };
}

#endif