#include "Events/EventDispatcher.hpp"
using namespace Scramble::Events;

EventDispatcher::HandlerArray EventDispatcher::handlers;

void EventDispatcher::DispatchEvent(Event* event)
{
    for(auto handler : handlers)
        handler->OnEvent(event);
}

void EventDispatcher::OnStartUp(GLFWwindow* windowHandle)
{
    glfwSetWindowCloseCallback(windowHandle, RaiseEvent<WindowCloseEvent>);
    glfwSetWindowSizeCallback(windowHandle, RaiseEvent<WindowResizeEvent, I32, I32>);
    glfwSetWindowPosCallback(windowHandle, RaiseEvent<WindowMovedEvent, I32, I32>);
    
    glfwSetKeyCallback(windowHandle, RaiseEvent<KeyEvent, I32, I32, I32, I32>);

    glfwSetMouseButtonCallback(windowHandle, RaiseEvent<MouseEvent, I32, I32, I32>);
    glfwSetCursorPosCallback(windowHandle, RaiseEvent<MouseMovedEvent, F64, F64>);
    glfwSetScrollCallback(windowHandle, RaiseEvent<MouseScrolledEvent, F64, F64>);
}
void EventDispatcher::OnShutDown()
{
    handlers.clear();
}

void EventDispatcher::PollEvents()
{
    glfwPollEvents();
}

U32 EventDispatcher::GetNumberOfHandlers()
{
    return handlers.size();
}

void EventDispatcher::AddHandler(EventHandler* handler)
{
    handlers.push_back(handler);
}
void EventDispatcher::RemoveHandler(EventHandler* handler)
{
    auto it = handlers.begin();

    for( ; it != handlers.end(); it++)
        if(*it == handler)
            handlers.erase(it);
}