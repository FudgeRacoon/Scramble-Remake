#ifndef OPENGL_VERTEXARRAY_HPP
#define OPENGL_VERTEXARRAY_HPP

#include "GLEW/glew.h"

#include "Core/Common/Types.hpp"
#include "Core/Debug/Assert.hpp"

#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"

namespace Scramble::Graphics
{
    class OpenGLVertexArray
    {
    private:
        U32 vertexArrayId;

    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();
    
    public:
        void SetVertexBuffer(OpenGLVertexBuffer* vbo);

    public:
        void Bind();
        void UnBind();
    };  
}

#endif