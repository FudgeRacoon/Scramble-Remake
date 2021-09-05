#ifndef MOUSE_EVENTS_HPP
#define MOUSE_EVENTS_HPP

#include "Core/Common/Types.hpp"

#include "Event.hpp"

namespace Scramble::Events
{
    class MouseEvent : public Event
    {
    protected:
        I32 button, mods;

    private:
        I32 action;

    public: 
        MouseEvent(I32 button, I32 action, I32 mods)
            :button(button), action(action), mods(mods) {}

    public:
        I32 GetButton()
        {
            return this->button;
        }
        I32 GetMods()
        {
            return this->mods;
        }
    
    public:
        EVENT_CLASS_TYPE(MouseAction)
    };

    class MouseButtonPressedEvent : public MouseEvent
    {
    public:
        MouseButtonPressedEvent(I32 button, I32 action, I32 mods)
            :MouseEvent(button, action, mods) {}

    public:
        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseEvent
    {
    public:
        MouseButtonReleasedEvent(I32 button, I32 action, I32 mods)
            :MouseEvent(button, action, mods) {}

    public:
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    class MouseMovedEvent : public Event
    {
    private:
        U32 x, y;

    public:
        MouseMovedEvent(U32 x, U32 y)
            :x(x), y(y) {}

    public:
        U32 GetX()
        {
            return this->x;
        }
        U32 GetY()
        {
            return this->y;
        }

    public:
        EVENT_CLASS_TYPE(MouseMoved)
    };

    class MouseScrolledEvent : public Event
    {
    private:
        I32 xoffset, yoffset;

    public:
        MouseScrolledEvent(I32 xoffset, I32 yoffset)
            :xoffset(xoffset), yoffset(yoffset) {}

    public:
        I32 GetXOffset()
        {
            return this->xoffset;
        }
        I32 GetYOffset()
        {
            return this->yoffset;
        }

    public:
        EVENT_CLASS_TYPE(MouseScrolled)
    };
}

#endif