#include "Graphics/OpenGL/OpenGLIndexBuffer.hpp"
using namespace Scramble::Graphics;

OpenGLIndexBuffer::OpenGLIndexBuffer(const U32* data, size bytes, U32 usage)
{
    glGenBuffers(1, &this->indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, data, usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &this->indexBufferId);
}

void OpenGLIndexBuffer::UpdateBufferData(size offsetBytes, size bytes, const U32* data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offsetBytes, bytes, data);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId);
}
void OpenGLIndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}