#include "Core/Window.hpp"
using namespace Scramble;

Window::Window(const WindowProps& props)
{
    this->title = props.title;
    
    this->width = props.width;
    this->height = props.height;
    
    this->fullscreen = props.fullscreen;
    this->vSync = props.vSync;

    Init();
}
Window::~Window()
{
    ShutDown();
}

void Window::Init()
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

    if(this->fullscreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        this->width = mode->width;
        this->height = mode->height;

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
    
    if(this->vSync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    this->running = true;
}
void Window::ShutDown()
{   
    glfwDestroyWindow(this->windowHandle);
    glfwTerminate();

    this->windowHandle = nullptr;
}

const char* Window::GetTitle()
{
    return this->title;
}

U32 Window::GetX()
{
    return this->x;
}
U32 Window::GetY()
{
    return this->y;
}
U32 Window::GetWidth()
{
    return this->width;
}
U32 Window::GetHeight()
{
    return this->height;
}

Window::NativeWindowHandle* Window::GetNativeHandle()
{
    return this->windowHandle;
}

void Window::SetTitle(const char* title)
{
    this->title = title;

    glfwSetWindowTitle(this->windowHandle, this->title);
}

void Window::SetX(U32 value)
{
    this->x = value;
}
void Window::SetY(U32 value)
{
    this->y = value;
}
void Window::SetWidth(U32 value)
{
    this->width = value;
}
void Window::SetHeight(U32 value)
{
    this->height = value;
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
void Window::SetVsync(bool value)
{
    if(value)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

bool Window::IsFullscreen()
{
    return this->fullscreen;
}
bool Window::IsRunning()
{
    return this->running;
}
bool Window::IsVsync()
{
    return this->vSync;
}

void Window::CloseWindow()
{
    this->running = false;
}