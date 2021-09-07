#include "Graphics/OpenGL/OpenGLVertexArray.hpp"
using namespace Scramble::Graphics;

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &this->vertexArrayId);
}
OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &this->vertexArrayId);
}

void OpenGLVertexArray::SetVertexBuffer(OpenGLVertexBuffer* vbo)
{
    glBindVertexArray(this->vertexArrayId);
    vbo->Bind();

    auto layouts = vbo->GetLayouts();

    SCRAMBLE_CORE_ASSERT_LOG(!layouts.empty(), "VertexBuffer must have a layout");

    int offset = 0;
    for(int index = 0; index < layouts.size(); index++)
    {
        OpenGLLayout layout = layouts[index];
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, layout.format, layout.type, layout.normalized, vbo->GetStride(), (const void*)offset);
        offset += layout.format * OpenGLLayout::GetSizeOfType(layout.type);
    }

    vbo->UnBind();
    glBindVertexArray(0);
}

void OpenGLVertexArray::Bind()
{
    glBindVertexArray(this->vertexArrayId);
}
void OpenGLVertexArray::UnBind()
{
    glBindVertexArray(0);
}