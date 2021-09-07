#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "Core/Common/Types.hpp"

#include "Event.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"
#include "ApplicationEvent.hpp"

namespace Scramble::Events
{
    class EventDispatcher;

    class EventHandler
    {
    typedef void(*WindowCloseCallback)();
    typedef void(*WindowResizeCallback)(WindowResizeEvent* event);
    typedef void(*WindowMoveCallback)(WindowMovedEvent* event);
    typedef void(*KeyPressCallback)(KeyPressedEvent* event);
    typedef void(*KeyReleaseCallback)(KeyReleasedEvent* event);
    typedef void(*MouseButtonPressCallback)(MouseButtonPressedEvent* event);
    typedef void(*MouseButtonReleaseCallback)(MouseButtonReleasedEvent* event);
    typedef void(*MouseMoveCallback)(MouseMovedEvent* event);
    typedef void(*MouseScrollCallback)(MouseScrolledEvent* event);

    private:
        WindowCloseCallback        windowCloseFunc = nullptr;
        WindowResizeCallback       windowResizeFunc = nullptr;
        WindowMoveCallback         windowMoveFunc = nullptr;
        KeyPressCallback           keyPressFunc = nullptr;
        KeyReleaseCallback         keyReleaseFunc = nullptr;
        MouseButtonPressCallback   mouseButtonPressFunc = nullptr;
        MouseButtonReleaseCallback mouseButtonReleaseFunc = nullptr;
        MouseMoveCallback          mouseMoveFunc = nullptr;
        MouseScrollCallback        mouseScrollFunc = nullptr;

    protected:
        EventHandler();
        
    protected:
        virtual ~EventHandler() = default;

    public:
        void SetOnWindowClose(WindowCloseCallback func);
        void SetOnWindowResize(WindowResizeCallback func);
        void SetOnWindowMove(WindowMoveCallback func);
        void SetOnKeyPress(KeyPressCallback func);
        void SetOnKeyRelease(KeyReleaseCallback func);
        void SetOnMouseButtonPress(MouseButtonPressCallback func);
        void SetOnMouseButtonRelease(MouseButtonReleaseCallback func);
        void SetOnMouseMove(MouseMoveCallback func);
        void SetOnMouseScroll(MouseScrollCallback func);

    public:
        void OnEvent(Event* event);
    };
}

#endif