#include "Graphics/OpenGL/Debug/OpenGLDebugger.hpp"
using namespace Scramble::Graphics;

void GLAPIENTRY OpenGLDebugger::OpenGLMessageCallback(U32 source, U32 type, U32 id, U32 severity, 
                                                      int length, const char* message, const void* userParam)
{
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         Logger::LogFatal(message); return;
        case GL_DEBUG_SEVERITY_MEDIUM:       Logger::LogError(message); return;
        case GL_DEBUG_SEVERITY_LOW:          Logger::LogWarning(message); return;
        case GL_DEBUG_SEVERITY_NOTIFICATION: Logger::LogInfo(message); return;
    }
}

void OpenGLDebugger::OnStartUp()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGLMessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
}