#include "Events/EventHandler.hpp"
using namespace Scramble::Events;

#include "Events/EventDispatcher.hpp"

EventHandler::EventHandler()
{
    EventDispatcher::AddHandler(this);
}

void EventHandler::SetOnWindowClose(WindowCloseCallback func)
{
    this->windowCloseFunc = func;
}
void EventHandler::SetOnWindowResize(WindowResizeCallback func)
{
    this->windowResizeFunc = func;
}
void EventHandler::SetOnWindowMove(WindowMoveCallback func)
{
    this->windowMoveFunc = func;
}
void EventHandler::SetOnKeyPress(KeyPressCallback func)
{
    this->keyPressFunc = func;
}
void EventHandler::SetOnKeyRelease(KeyReleaseCallback func)
{
    this->keyReleaseFunc = func;
}
void EventHandler::SetOnMouseButtonPress(MouseButtonPressCallback func)
{
    this->mouseButtonPressFunc = func;
}
void EventHandler::SetOnMouseButtonRelease(MouseButtonReleaseCallback func)
{
    this->mouseButtonReleaseFunc = func;
}
void EventHandler::SetOnMouseMove(MouseMoveCallback func)
{
    this->mouseMoveFunc = func;
}
void EventHandler::SetOnMouseScroll(MouseScrollCallback func)
{
    this->mouseScrollFunc = func;
}

void EventHandler::OnEvent(Event* event)
{
    switch (event->GetEventType())
    {
        case EventType::WindowClose:         if(windowCloseFunc) windowCloseFunc(); break;
        case EventType::WindowResize:        if(windowResizeFunc) windowResizeFunc(dynamic_cast<WindowResizeEvent*>(event)); break;
        case EventType::WindowMoved:         if(windowMoveFunc) windowMoveFunc(dynamic_cast<WindowMovedEvent*>(event)); break;

        case EventType::KeyPressed:          if(keyPressFunc) keyPressFunc(dynamic_cast<KeyPressedEvent*>(event)); break;
        case EventType::KeyReleased:         if(keyReleaseFunc) keyReleaseFunc(dynamic_cast<KeyReleasedEvent*>(event)); break;
        
        case EventType::MouseButtonPressed:  if(mouseButtonPressFunc) mouseButtonPressFunc(dynamic_cast<MouseButtonPressedEvent*>(event)); break;
        case EventType::MouseButtonReleased: if(mouseButtonReleaseFunc) mouseButtonReleaseFunc(dynamic_cast<MouseButtonReleasedEvent*>(event)); break;
        case EventType::MouseMoved:          if(mouseMoveFunc) mouseMoveFunc(dynamic_cast<MouseMovedEvent*>(event)); break;
        case EventType::MouseScrolled:       if(mouseScrollFunc) mouseScrollFunc(dynamic_cast<MouseScrolledEvent*>(event)); break;
    }
}