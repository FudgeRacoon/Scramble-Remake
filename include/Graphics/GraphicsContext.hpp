#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include <stdlib.h>

#include "GLEW/glew.h"

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"
#include "Core/Window.hpp"

namespace Scramble::Graphics
{
    class GraphicsContext
    {
    private:
        static Window::NativeWindowHandle* handle;
    
    private:
        GraphicsContext() = delete;

    public:
        static void OnStartUp(Window::NativeWindowHandle* handle);

    public:
        static I32 GetMaxTextureSlots();
        static const byte* GetAPIVendor();
        static const byte* GetAPIVersion();
        static const byte* GetAPIRenderer();

    public:
        static void SwapBuffers();
    };
    
}

#endif