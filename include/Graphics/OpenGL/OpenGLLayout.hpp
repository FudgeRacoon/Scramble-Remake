#ifndef OPENGL_LAYOUT_HPP
#define OPENGL_LAYOUT_HPP

#include "GLEW/glew.h"

#include "Core/Common/Types.hpp"

namespace Scramble::Graphics
{
    struct OpenGLLayout
    {
        U32 type;
        U32 format;
        bool normalized;

        static size GetSizeOfType(U32 type);
    };
}

#endif