#ifndef OPENGL_VERTEXBUFFER_HPP
#define OPENGL_VERTEXBUFFER_HPP

#include <vector>
#include <type_traits>

#include "GLEW/glew.h"

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"

#include "OpenGLLayout.hpp"

namespace Scramble::Graphics
{
    class OpenGLVertexBuffer
    {
    using LayoutArray = std::vector<OpenGLLayout>;

    private:
        U32 vertexBufferId;

    private:
        size stride;
        LayoutArray layouts;

    public:
        OpenGLVertexBuffer(const void* data, size bytes, U32 usage);
        ~OpenGLVertexBuffer();

    public:
        size GetStride();
        LayoutArray GetLayouts();

    public:
        template<typename T>
        void AddLayout(int format, bool normalized)
        {
            if(std::is_same<T,float>::value)
            {
                OpenGLLayout layout;
                layout.type = GL_FLOAT;
                layout.format = format;
                layout.normalized = normalized;

                this->stride += layout.format * sizeof(float);

                this->layouts.push_back(layout);
            }
            else if(std::is_same<T,unsigned int>::value)
            {
                OpenGLLayout layout;
                layout.type = GL_UNSIGNED_INT;
                layout.format = format;
                layout.normalized = normalized;

                this->stride += layout.format * sizeof(unsigned int);

                this->layouts.push_back(layout);
            }
            else if(std::is_same<T,unsigned char>::value)
            {
                OpenGLLayout layout;
                layout.type = GL_UNSIGNED_BYTE;
                layout.format = format;
                layout.normalized = normalized;

                this->stride += layout.format * sizeof(unsigned char);

                this->layouts.push_back(layout);
            }
            else
            {
                Logger::LogError("Failed to add buffer layout due to being an unsupported type");
                return;
            }
        }

    public:
        void UpdateBufferData(size offsetBytes, size bytes, const void* data);

    public:
        void Bind();
        void UnBind();
    };  
}

#endif