#ifndef APPLICATION_EVENT_HPP
#define APPLICATION_EVENT_HPP

#include "Core/Common/Types.hpp"

#include "Event.hpp"

namespace Scramble::Events
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

    public:
        EVENT_CLASS_TYPE(WindowClose)
    };

    class WindowResizeEvent : public Event
    {
    private:
        U32 width, height;

    public:
        WindowResizeEvent(U32 width, U32 height)
            : width(width), height(height) {}

    public:
        U32 GetWidth() const 
        {
            return this->width; 
        }
        U32 GetHeight() const
        {
            return this->height;
        }
    
    public:
        EVENT_CLASS_TYPE(WindowResize)
    };

    class WindowMovedEvent : public Event
    {
    private:
        U32 x, y;
    
    public:
        WindowMovedEvent(U32 x, U32 y)
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
        EVENT_CLASS_TYPE(WindowMoved)
    };
}

#endif