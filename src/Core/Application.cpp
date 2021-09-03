#include "Core/Application.hpp"
using namespace Scramble;

std::unique_ptr<Window> Application::windowContext;
std::unique_ptr<RuntimeInstance> Application::runtimeContext;

void Application::Start(RuntimeInstance* instance)
{
    Time::OnStartUp();
    
    windowContext = std::unique_ptr<Window>(new Window());
    runtimeContext = std::unique_ptr<RuntimeInstance>(instance);

    Input::KeyListener::OnStartUp();
    Input::MouseListener::OnStartUp();
    Input::InputManager::OnStartUp();

    windowContext->SetOnWindowClose([] (Window::NativeWindowHandle*) {windowContext->CloseWindow();});
    windowContext->SetOnWindowPos([] (Window::NativeWindowHandle*, int x, int y) {windowContext->SetX(x); windowContext->SetY(y);});
    windowContext->SetOnWindowResize([] (Window::NativeWindowHandle*, int width, int height) {windowContext->SetWidth(width);windowContext->SetHeight(height);});
    
    windowContext->SetOnKeyAction(Input::KeyListener::KeyCallback);
    windowContext->SetOnMouseMotion(Input::MouseListener::MousePosCallback);
    windowContext->SetOnMouseAction(Input::MouseListener::MouseButtonCallback);
    windowContext->SetOnMouseScroll(Input::MouseListener::MouseScrollCallback);

    Graphics::GraphicsContext::OnStartUp(windowContext->GetNativeHandle());
    Graphics::RenderCommand::OnStartUp(0, 0, windowContext->GetWidth(), windowContext->GetHeight());
    Graphics::Renderer::OnStartUp();
    Graphics::OpenGLDebugger::OnStartUp();
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
                    Logger::LogWarning("%.2fms lag has occured.", lag * 1000.0);
            #endif
            
            windowContext->PollEvents();

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

    Input::KeyListener::OnShutDown(); 
    Input::MouseListener::OnShutDown();

    windowContext.reset(nullptr);
    runtimeContext.reset(nullptr);
}