#include "Core/Window.hpp"
using namespace Scramble;

Window::Window(const WindowProps& props)
{
    this->title = props.title;
    
    this->width = props.width;
    this->height = props.height;
    
    this->fullscreen = props.fullscreen;
    this->vSync = props.vSync;

    Internal_Init();
}
Window::~Window()
{
    Internal_ShutDown();
}

void Window::Internal_Init()
{
    if(glfwInit() != GLFW_TRUE)
    {
        S_FATAL("Failed to initialize GLFW");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    glfwWindowHint(GLFW_CLIENT_API , GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Internal_CreateWindow();

    if(this->vSync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    this->running = true;
}
void Window::Internal_ShutDown()
{   
    glfwDestroyWindow(this->windowHandle);
    glfwTerminate();

    this->windowHandle = nullptr;
}
void Window::Internal_CreateWindow()

{
    if(this->fullscreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        
        this->width = mode->width;
        this->height = mode->height;
        
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        this->windowHandle = glfwCreateWindow(
            this->width,
            this->height,
            this->title,
            monitor,
            nullptr
        );
    }
    else
    {
        this->windowHandle = glfwCreateWindow(
            this->width,
            this->height,
            this->title,
            nullptr,
            nullptr
        );
    }
    
    if(!this->windowHandle)
    {
        S_FATAL("Failed to create a GLFW window");       
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

const char* Window::GetTitle()
{
    return this->title;
}
Window::NativeWindowHandle* Window::GetNativeHandle()
{
    return this->windowHandle;
}

bool Window::IsVsync()
{
    return this->vSync;
}
bool Window::IsRunning()
{
    return this->running;
}
bool Window::IsFullscreen()
{
    return this->fullscreen;
}

void Window::SetTitle(const char* title)
{
    this->title = title;

    glfwSetWindowTitle(this->windowHandle, this->title);
}

void Window::SetVsync(bool value)
{
    if(value)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}
void Window::SetFullscreen(bool value)
{
    if(this->fullscreen == value)
        return;

    this->fullscreen = value;

    if(value)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(
            this->windowHandle,
            monitor,
            0,
            0,
            this->width,
            this->height,
            mode->refreshRate
        );
    }
    else
    {
        glfwSetWindowMonitor(
            this->windowHandle,
            nullptr,
            this->x,
            this->y,
            this->width,
            this->height,
            0
        );
    }
}

void Window::CloseWindow()
{
    this->running = false;
}