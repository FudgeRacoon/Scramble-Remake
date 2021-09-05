#include "Core/Application.hpp"
using namespace Scramble;

std::unique_ptr<Window> Application::windowContext;
std::unique_ptr<RuntimeInstance> Application::runtimeContext;

float counter = 0.0;
#define SCRAMBLE_NO_DEBUG

void Application::Start(RuntimeInstance* instance)
{
    Time::OnStartUp();

    windowContext = std::unique_ptr<Window>(new Window());
    runtimeContext = std::unique_ptr<RuntimeInstance>(instance);

    Events::EventDispatcher::OnStartUp(windowContext->GetNativeHandle());
    
    windowContext->SetOnMouseMove([] (MouseMovedEvent* e)
        {
            S_DEBUG("%d %d", e->GetX(), e->GetY());
        }
    );

    Input::KeyListener::OnStartUp();
    Input::MouseListener::OnStartUp();
    Input::InputManager::OnStartUp();

    Graphics::GraphicsContext::OnStartUp(windowContext->GetNativeHandle());
    Graphics::RenderCommand::OnStartUp(0, 0, windowContext->GetWidth(), windowContext->GetHeight());
    Graphics::OpenGLDebugger::OnStartUp();

    ResourceManager::OnStartUp();
    Graphics::Renderer::OnStartUp();
}
void Application::Run()
{
    runtimeContext->OnEnter();
    
    while(windowContext->IsRunning())
    {
        Time::OnUpdate();

        if(Time::GetDeltaTime() >= (1.0 / 60.0))
        {
            #ifndef SCRAMBLE_NO_DEBUG
                double lag = Time::GetDeltaTime() - (1.0 / 60.0);
                if(lag > 0.004)
                    S_WARN("%.2fms lag has occured.", lag * 1000.0);
            #endif
            
            Events::EventDispatcher::PollEvents();

            Graphics::RenderCommand::Clear();

            runtimeContext->OnUpdate();

            Graphics::GraphicsContext::SwapBuffers();
            
            Input::InputManager::OnFrameEnd();
            
            Time::OnFrameEnd();
        }
    }

    runtimeContext->OnExit();
}
void Application::ShutDown()
{
    Graphics::Renderer::OnShutDown();
    ResourceManager::OnShutDown();

    Input::KeyListener::OnShutDown(); 
    Input::MouseListener::OnShutDown();

    Events::EventDispatcher::OnShutDown();

    windowContext.reset(nullptr);
    runtimeContext.reset(nullptr);
}