#ifndef RENDERER_CONTEXT_HPP
#define RENDERER_CONTEXT_HPP

#include "Core/Common/Types.hpp"
#include "Core/Geometry/Line.hpp"
#include "Core/Geometry/Rect.hpp"
#include "Core/Math/Color.hpp"
#include "Core/Math/Matrix4.hpp"
#include "Core/Math/Vector2.hpp"
#include "Core/Math/Vector3.hpp"
#include "Core/Math/Vector4.hpp"

#include "OpenGL/OpenGLVertexBuffer.hpp"
#include "OpenGL/OpenGLIndexBuffer.hpp"
#include "OpenGL/OpenGLVertexArray.hpp"
#include "OpenGL/OpenGLShader.hpp"
#include "OpenGL/OpenGLTexture.hpp"
#include "GraphicsContext.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"

#include "Scene/Camera.hpp"
using namespace Scene;

namespace Scramble::Graphics
{
    struct VertexData
    {
        Vector3 position;
        Vector4 pixelColor;
        Vector2 textureCoords;
        F32     textureShaderSlot;
    };

    struct RendererContext
    {
        const U32                    MAX_LINES              = 10000;
        const size                   LINE_VERTICES_SIZE     = 10 * 2 * sizeof(float);
        const size                   MAX_LINE_VERTICES_SIZE = MAX_LINES * LINE_VERTICES_SIZE;

        const U32                    MAX_QUADS              = 10000;
        const size                   QUAD_VERTICES_SIZE     = 10 * 4 * sizeof(float);
        const size                   QUAD_INDICIES_SIZE     = 6 * sizeof(U32);
        const size                   MAX_QUAD_VERTICES_SIZE = MAX_QUADS * QUAD_VERTICES_SIZE;
        const size                   MAX_QUAD_INDICIES_SIZE = MAX_QUADS * QUAD_INDICIES_SIZE;

        OpenGLVertexBuffer*          lineVertexBuffer = nullptr;
        OpenGLVertexBuffer*          quadVertexBuffer = nullptr;
        OpenGLVertexArray*           lineVertexArray  = nullptr;
        OpenGLVertexArray*           quadVertexArray  = nullptr;
        OpenGLIndexBuffer*           quadIndexBuffer  = nullptr;
        
        WeakPtr<Texture>*            textureSlots     = nullptr;
        WeakPtr<Shader>              registeredShader;
        SharedPtr<Camera>            registeredCamera;

        VertexData*                  lineVertexDataPtr  = nullptr;
        VertexData*                  lineVertexDataBase = nullptr;
        VertexData*                  quadVertexDataPtr  = nullptr;
        VertexData*                  quadVertexDataBase = nullptr;

        U32                          lineCount          = 0;
        U32                          quadCount          = 0;
        U32                          currentTextureSlot = 1;
    };
}

#endif