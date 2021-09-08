#include "Core/Application.hpp"
using namespace Scramble;

UniquePtr<Window> Application::windowContext;
UniquePtr<RuntimeInstance> Application::runtimeContext;

#define SCRAMBLE_NO_DEBUG

void Application::Start(RuntimeInstance* instance)
{
    Time::OnStartUp();

    windowContext = UniquePtr<Window>(new Window());
    runtimeContext = UniquePtr<RuntimeInstance>(instance);

    Events::EventDispatcher::OnStartUp(windowContext->GetNativeHandle());
    
    Input::InputManager::OnStartUp();
    
    Graphics::GraphicsContext::OnStartUp(windowContext->GetNativeHandle());
    Graphics::RenderCommand::OnStartUp(0, 0, windowContext->width, windowContext->height);
    Graphics::OpenGLDebugger::OnStartUp();

    ResourceManager::OnStartUp();
    Graphics::Renderer::OnStartUp();

    Physics::PhysicsSystem::OnStartUp(Vector3(0.0, -10.0, 0.0), 1.0 / 120.0);

    windowContext->SetOnWindowClose([] () {windowContext->CloseWindow();});
    windowContext->SetOnWindowMove([] (WindowMovedEvent* e) {windowContext-> x = e->GetX(); windowContext->y = e->GetY();});
    windowContext->SetOnWindowResize([] (WindowResizeEvent* e) {windowContext->width = e->GetWidth(); windowContext->height = e->GetHeight();});
}
void Application::Run()
{
    runtimeContext->OnEnter();
    
    while(windowContext->IsRunning())
    {
        Time::OnUpdate();

        if(Time::GetDeltaTime() >= (1.0 / 120.0))
        {
            #ifndef SCRAMBLE_NO_DEBUG
                double lag = Time::GetDeltaTime() - (1.0 / 60.0);
                if(lag > 0.004)
                    S_WARN("%.2fms lag has occured.", lag * 1000.0);
            #endif
            
            Events::EventDispatcher::PollEvents();

            Graphics::RenderCommand::Clear();

            Physics::PhysicsSystem::FixedUpdate();

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
    Physics::PhysicsSystem::OnShutDown();

    Graphics::Renderer::OnShutDown();
    ResourceManager::OnShutDown();
    
    Events::EventDispatcher::OnShutDown();

    windowContext.reset(nullptr);
    runtimeContext.reset(nullptr);
}