#ifndef MOUSELISTENER_HPP
#define MOUSELISTENER_HPP

#include <string.h>

#include "GLFW/glfw3.h"

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"

#include "Events/MouseEvent.hpp"
#include "Events/EventHandler.hpp"
using namespace Scramble::Events;

namespace Scramble::Input
{
    class MouseListener : public EventHandler
    {
    private:
        I32* x; 
        I32* y;
        I32* xOffset; 
        I32* yOffset;
        byte* mouseState;

    private:
        MouseListener();

    public:
        ~MouseListener();

    public:
        static MouseListener* GetInstance();

    public:
        const byte* GetMouseState(I32*& x, I32*& y, I32*& xOffset, I32*& yOffset);
    };
}

#endif