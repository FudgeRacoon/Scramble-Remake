#ifndef EVENT_HPP
#define EVENT_HPP

namespace Scramble::Events
{
    enum EventType
    {
        None = 0,

        KeyAction,
        MouseAction,

        WindowClose, 
        WindowResize, 
        WindowMoved,
        WindowFocus, 
        WindowLostFocus, 

        KeyPressed, 
        KeyReleased,

        MouseButtonPressed, 
        MouseButtonReleased, 
        MouseMoved, 
        MouseScrolled
    };

    class Event
    {
    public:
        virtual EventType GetEventType() = 0;
        virtual const char* GetEventName() = 0;
    };

    #define EVENT_CLASS_TYPE(type)\
        EventType GetEventType() override {return EventType::type;}\
        const char* GetEventName() override {return #type;}
}

#endif