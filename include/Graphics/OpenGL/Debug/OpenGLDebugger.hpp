#ifndef OPENGL_DEBUGGER_HPP
#define OPENGL_DEBUGGER_HPP

#include "GLEW/glew.h"

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"

namespace Scramble::Graphics
{
    class OpenGLDebugger
    {
    private:
        OpenGLDebugger() = delete;
        ~OpenGLDebugger() = delete;

    private:
        static void GLAPIENTRY OpenGLMessageCallback(U32 source, U32 type, U32 id, U32 severity, 
                                                     int length, const char* message, const void* userParam);

    public:
        static void OnStartUp();
    };
}

#endif