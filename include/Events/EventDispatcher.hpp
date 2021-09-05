#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include <vector>
#include <type_traits>

#include "GLFW/glfw3.h"

#include "Core/Common/Types.hpp"

#include "Event.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"
#include "ApplicationEvent.hpp"
#include "ApplicationEvent.hpp"
#include "EventHandler.hpp"

namespace Scramble::Events
{
    class EventDispatcher
    {
    typedef std::vector<EventHandler*> HandlerArray;

    private:    
        static HandlerArray handlers;
    
    private:
        EventDispatcher() = delete;
        ~EventDispatcher() = delete;

    private:
        template<typename EventType, typename... EventArgs>
        static void RaiseEvent(GLFWwindow* windowHandle, EventArgs... args)
        {
            I32 eventArgs[4] = {args...};

            if(std::is_same<EventType, KeyEvent>::value)
            {
                if(eventArgs[2] == GLFW_PRESS)
                {
                    KeyPressedEvent event(eventArgs[0], eventArgs[1], eventArgs[2], eventArgs[3]);
                    DispatchEvent(&event);
                    return;
                }
                else if(eventArgs[2] == GLFW_RELEASE)
                {
                    KeyReleasedEvent event(eventArgs[0], eventArgs[1], eventArgs[2], eventArgs[3]);
                    DispatchEvent(&event);
                    return;
                }
            }

            if(std::is_same<EventType, MouseEvent>::value)
            {
                if(eventArgs[1] == GLFW_PRESS)
                {
                    MouseButtonPressedEvent event(eventArgs[0], eventArgs[1], eventArgs[2]);
                    DispatchEvent(&event);
                    return;
                }
                else if(eventArgs[1] == GLFW_RELEASE)
                {
                    MouseButtonReleasedEvent event(eventArgs[0], eventArgs[1], eventArgs[2]);
                    DispatchEvent(&event);
                    return;
                }
            }
            
            EventType event(args...);
            DispatchEvent(&event);  
        }
        
    private:
        static void DispatchEvent(Event* event);

    public:
        static void OnStartUp(GLFWwindow* windowHandle);
        static void OnShutDown();

    public:
        static void PollEvents();

    public:
        static U32 GetNumberOfHandlers();
    
    public:
        static void AddHandler(EventHandler* handler);
        static void RemoveHandler(EventHandler* handler);
    };
}

#endif