#ifndef OPENGL_INDEXBUFFER_HPP
#define OPENGL_INDEXBUFFER_HPP

#include "GLEW/glew.h"

#include "Core/Common/Types.hpp"

namespace Scramble::Graphics
{
    class OpenGLIndexBuffer
    {
    private:
        U32 indexBufferId;

    public:
        OpenGLIndexBuffer(const U32* data, size bytes, U32 usage);
        ~OpenGLIndexBuffer();

    public:
        void UpdateBufferData(size offsetBytes, size bytes, const U32* data);

    public:
        void Bind() const;
        void UnBind() const;
    };  
}

#endif