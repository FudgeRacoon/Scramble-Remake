#ifndef KEY_EVENT_HPP
#define KEY_EVENT_HPP

#include "Core/Common/Types.hpp"

#include "Event.hpp"

namespace Scramble::Events
{
    class KeyEvent : public Event
    {
    protected:
        I32 key, scancode, mods;
    
    private:
        I32 action;

    public:
        KeyEvent(I32 key, I32 scancode, I32 action, I32 mods)
            :key(key), scancode(scancode), action(action), mods(mods) {}

    public:
        I32 GetKey()
        {
            return this->key;
        }
        I32 GetScancode()
        {
            return this->scancode;
        }
        I32 GetMods()
        {
            return this->mods;
        }
    
    public:
        EVENT_CLASS_TYPE(KeyAction)
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(I32 key, I32 scancode, I32 action, I32 mods)
            :KeyEvent(key, scancode, action, mods) {}

    public:
        EVENT_CLASS_TYPE(KeyPressed);
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(I32 key, I32 scancode, I32 action, I32 mods)
            :KeyEvent(key, scancode, action, mods) {}

    public:
        EVENT_CLASS_TYPE(KeyReleased);
    };
}

#endif