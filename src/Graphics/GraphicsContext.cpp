#include "Graphics/GraphicsContext.hpp"
using namespace Scramble;
using namespace Scramble::Graphics;

Window::NativeWindowHandle* GraphicsContext::handle = nullptr;

void GraphicsContext::OnStartUp(Window::NativeWindowHandle* handle)
{ 
    S_INFO("GraphicsContext is starting up...");

    GraphicsContext::handle = handle;
    glfwMakeContextCurrent(GraphicsContext::handle);

    glewExperimental = true;
    if(glewInit() != 0)
    {
        Logger::LogFatal("Failed to initialize GLEW");
        exit(EXIT_FAILURE);
    }

    Logger::LogDebug("%s", GetAPIVendor());
    Logger::LogDebug("%s", GetAPIVersion());
    Logger::LogDebug("%s", GetAPIRenderer());
}

I32 GraphicsContext::GetMaxTextureSlots()
{
    I32 maxSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxSlots);
    return maxSlots;
}
const byte* GraphicsContext::GetAPIVendor()
{
    return glGetString(GL_VENDOR);
}
const byte* GraphicsContext::GetAPIVersion()
{
    return glGetString(GL_VERSION);
}
const byte* GraphicsContext::GetAPIRenderer()
{
    return glGetString(GL_RENDERER);
}

void GraphicsContext::SwapBuffers()
{   
    glfwSwapBuffers(GraphicsContext::handle);
}