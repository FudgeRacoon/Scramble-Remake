#ifndef RENDER_COMMAND_HPP
#define RENDER_COMMAND_HPP

#include "GLEW/glew.h"

#include "Core/Common/Types.hpp"
#include "Core/Geometry/Rect.hpp"

#include "Graphics/OpenGL/OpenGLIndexBuffer.hpp"
#include "Graphics/OpenGL/OpenGLVertexArray.hpp"
#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"
using namespace Scramble;

namespace Scramble::Graphics
{
    class RenderCommand
    {
    private:
        RenderCommand() = delete;
        ~RenderCommand() = delete;

    public:
        static void OnStartUp(U32 x, U32 y, U32 width, U32 height);

    public:
        static Rect GetViewport();

    public:
        static void SetDrawBuffer(I32 mode);
        static void SetBlendFunc(I32 sFactor, I32 dFactor);
        static void SetViewport(U32 x, U32 y, U32 width, U32 height);
        static void SetClearColor(float r, float g, float b);

    public:
        static void Clear();
        static void DrawArrays(I32 mode, OpenGLVertexArray* vao, U32 vertices);
        static void DrawElements(I32 mode, OpenGLVertexArray* vao, OpenGLIndexBuffer* ibo, U32 indicies);
    };
}

#endif