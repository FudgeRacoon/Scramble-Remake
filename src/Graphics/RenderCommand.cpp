#include "Graphics/RenderCommand.hpp"
using namespace Scramble::Graphics;

void RenderCommand::OnStartUp(U32 x, U32 y, U32 width, U32 height)
{
    S_INFO("RenderCommand is starting up...");

    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glViewport(x, y, width, height);
    glClearColor(0.08, 0.08, 0.08, 1.0);

    glDrawBuffer(GL_BACK);
}

Rect RenderCommand::GetViewport()
{
    int data[4];
    glGetIntegerv(GL_VIEWPORT, data);
    return Rect(data[0], data[1], data[2], data[3]);
}

void RenderCommand::SetDrawBuffer(I32 mode)
{
    glDrawBuffer(mode);
}
void RenderCommand::SetBlendFunc(I32 sFactor, I32 dFactor)
{
    glBlendFunc(sFactor, dFactor);
}
void RenderCommand::SetViewport(U32 x, U32 y, U32 width, U32 height)
{
    glViewport(x, y, width, height);
}
void RenderCommand::SetClearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0);
}

void RenderCommand::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void RenderCommand::DrawArrays(I32 mode, OpenGLVertexArray* vao, U32 vertices)
{
    vao->Bind();
    glDrawArrays(mode, 0, vertices);
    vao->UnBind();
}
void RenderCommand::DrawElements(I32 mode, OpenGLVertexArray* vao, OpenGLIndexBuffer* ibo, U32 indicies)
{
    vao->Bind();
    ibo->Bind();
    glDrawElements(mode, indicies, GL_UNSIGNED_INT, nullptr);
    ibo->UnBind();
    vao->UnBind();
}