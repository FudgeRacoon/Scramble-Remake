#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"
using namespace Scramble::Graphics;

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, size bytes, U32 usage)
{
    this->stride = 0;

    glGenBuffers(1, &this->vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, bytes, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    this->layouts.clear();

    glDeleteBuffers(1, &this->vertexBufferId);
}

size OpenGLVertexBuffer::GetStride()
{
    return this->stride;
}
OpenGLVertexBuffer::LayoutArray OpenGLVertexBuffer::GetLayouts()
{
    return this->layouts;
}

void OpenGLVertexBuffer::UpdateBufferData(size offsetBytes, size bytes, const void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
    glBufferSubData(GL_ARRAY_BUFFER, offsetBytes, bytes, data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);
}
void OpenGLVertexBuffer::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}