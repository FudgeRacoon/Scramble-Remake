#include "Graphics/Renderer.hpp"
using namespace Scramble::Graphics;

RendererContext Renderer::context;

void Renderer::StartBatch()
{
    context.lineCount = 0;
    context.quadCount = 0;

    context.currentTextureSlot = 1;

    context.lineVertexDataPtr = context.lineVertexDataBase;
    context.quadVertexDataPtr = context.quadVertexDataBase;
}
void Renderer::NextBatch()
{
    Flush();
    StartBatch();
}
void Renderer::Flush()
{
    SCRAMBLE_CORE_ASSERT_LOG(context.registeredCamera, "Registerd camera is null!");
    SCRAMBLE_CORE_ASSERT_LOG(!context.textureSlots[0].expired(), "White texture has an invalid address!");
    SCRAMBLE_CORE_ASSERT_LOG(!context.registeredShader.expired(), "Registered shader has an invalid address!");

    context.registeredShader.lock()->GetNativeShader()->Bind();

    for(int i = 0; i < context.currentTextureSlot; i++)
        context.textureSlots[i].lock()->GetNativeTexture()->Bind(i);

    context.lineVertexBuffer->UpdateBufferData(0, context.LINE_VERTICES_SIZE * context.lineCount, context.lineVertexDataBase);
    context.quadVertexBuffer->UpdateBufferData(0, context.QUAD_VERTICES_SIZE * context.quadCount, context.quadVertexDataBase);

    context.registeredShader.lock()->SetMat4(
        "uViewMatrix",
        context.registeredCamera->GetViewMatrix()
    );
    context.registeredShader.lock()->SetMat4(
        "uProjMatrix",
        context.registeredCamera->GetProjectionMatrix()
    );

    RenderCommand::DrawArrays(
        GL_LINES,
        context.lineVertexArray,
        context.lineCount * 2
    );
    RenderCommand::DrawElements(
        GL_TRIANGLES,
        context.quadVertexArray,
        context.quadIndexBuffer,
        context.quadCount * 6
    );

    for(int i = 0; i < context.currentTextureSlot; i++)
        context.textureSlots[i].lock()->GetNativeTexture()->UnBind();

    context.registeredShader.lock()->GetNativeShader()->UnBind();
}

U32 Renderer::GetTextureSlot(WeakPtr<Texture> texture)
{
    for(int i = 0; i < context.currentTextureSlot; i++)
    {
        if(context.textureSlots[i].lock()->GetNativeTexture()->GetNativeId() == texture.lock()->GetNativeTexture()->GetNativeId())
            return i;
    }

    context.textureSlots[context.currentTextureSlot] = texture;
    return context.currentTextureSlot++;
}

void Renderer::InitBuffers()
{
    context.lineVertexArray = new OpenGLVertexArray();
    context.lineVertexBuffer = new OpenGLVertexBuffer(nullptr, context.MAX_LINE_VERTICES_SIZE, GL_DYNAMIC_DRAW);
    context.lineVertexBuffer->AddLayout<float>(3, false);
    context.lineVertexBuffer->AddLayout<float>(4, false);
    context.lineVertexBuffer->AddLayout<float>(2, false);
    context.lineVertexBuffer->AddLayout<float>(1, false);
    context.lineVertexArray->SetVertexBuffer(context.lineVertexBuffer);

    context.quadVertexArray = new OpenGLVertexArray();
    context.quadVertexBuffer = new OpenGLVertexBuffer(nullptr, context.MAX_QUAD_VERTICES_SIZE, GL_DYNAMIC_DRAW);
    context.quadVertexBuffer->AddLayout<float>(3, false);
    context.quadVertexBuffer->AddLayout<float>(4, false);
    context.quadVertexBuffer->AddLayout<float>(2, false);
    context.quadVertexBuffer->AddLayout<float>(1, false);
    context.quadVertexArray->SetVertexBuffer(context.quadVertexBuffer);

    U32 offset = 0;
    U32 indicies[context.MAX_QUADS * 6];
    for(int i = 0; i < context.MAX_QUADS * 6; i += 6)
    {
        indicies[i + 0] = 0 + offset;
        indicies[i + 1] = 1 + offset;
        indicies[i + 2] = 2 + offset;
        indicies[i + 3] = 2 + offset;
        indicies[i + 4] = 3 + offset;
        indicies[i + 5] = 0 + offset;

        offset += 4;
    }

    context.quadIndexBuffer = new OpenGLIndexBuffer(indicies, context.MAX_QUAD_INDICIES_SIZE, GL_STATIC_DRAW);
}
void Renderer::InitShaders()
{
    context.registeredShader = ResourceManager::GetShader("Default_Shader");
}
void Renderer::InitTextures()
{
    context.textureSlots = new WeakPtr<Texture>[GraphicsContext::GetMaxTextureSlots()];
    context.textureSlots[0] = ResourceManager::GetTexture("White_Texture");
}

void Renderer::OnStartUp()
{
    S_INFO("Renderer is starting up...");

    InitBuffers();
    InitShaders();
    InitTextures();

    context.lineVertexDataBase = new VertexData[context.MAX_LINES * 2];
    context.lineVertexDataPtr = context.lineVertexDataBase;

    context.quadVertexDataBase = new VertexData[context.MAX_QUADS * 4];
    context.quadVertexDataPtr = context.quadVertexDataBase;
}
void Renderer::OnShutDown()
{
    delete context.lineVertexBuffer;
    delete context.lineVertexArray;

    delete context.quadVertexBuffer;
    delete context.quadIndexBuffer;
    delete context.quadVertexArray;

    delete[] context.lineVertexDataBase;
    delete[] context.quadVertexDataBase;

    delete[] context.textureSlots; 
}

void Renderer::BeginScene(Camera* camera)
{
    StartBatch();
    context.registeredCamera = camera; 
}
void Renderer::EndScene()
{
    Flush();
    context.registeredCamera = nullptr;
}

WeakPtr<Shader> Renderer::GetRegisteredShader()
{
    return context.registeredShader;
}
void Renderer::RegisterShader(WeakPtr<Shader> shader)
{
    context.registeredShader = shader;
}

void Renderer::DrawLine(Line line, Color color)
{
    if(context.lineCount > context.MAX_LINES)
        NextBatch();

    for(int i = 0; i < 2; i++)
    {
        context.lineVertexDataPtr->position = i == 0 ? line.start : line.end;
        context.lineVertexDataPtr->pixelColor = (Vector4)color;
        context.lineVertexDataPtr->textureCoords = Vector2();
        context.lineVertexDataPtr->textureShaderSlot = 0;
        context.lineVertexDataPtr++;
    }

    context.lineCount++;
}
void Renderer::DrawLine(Vector3 start, Vector3 end, Color color)
{
    DrawLine(Line(start, end), color);
}
void Renderer::DrawLine(float x0, float y0, float x1, float y1, Color color)
{
    DrawLine(Line(x0, y0, x1, y1), color);
}

void Renderer::DrawQuad(Rect rect, Color color)
{
    DrawLine(rect.GetX(), rect.GetY(), rect.GetXMax(), rect.GetY(), color);
    DrawLine(rect.GetX(), rect.GetYMax(), rect.GetXMax(), rect.GetYMax(), color);
    DrawLine(rect.GetX(), rect.GetY(), rect.GetX(), rect.GetYMax(), color);
    DrawLine(rect.GetXMax(), rect.GetY(), rect.GetXMax(), rect.GetYMax(), color);
}
void Renderer::DrawQuad(Vector3 position, Vector3 size, Color color)
{
    DrawQuad(Rect(position, size), color);
}
void Renderer::DrawQuad(float x, float y, float width, float height, Color color)
{
    DrawQuad(Rect(x, y, width, height), color);
}

void Renderer::DrawFilledQuad(Rect rect, Color color)
{
    if(context.quadCount > context.MAX_QUADS)
        NextBatch();

    Vector3 position;
    for(int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0: position = Vector3(rect.GetX(), rect.GetYMax(), 0.0); break;
            case 1: position = Vector3(rect.GetXMax(), rect.GetYMax(), 0.0); break;
            case 2: position = Vector3(rect.GetXMax(), rect.GetY(), 0.0); break;
            case 3: position = Vector3(rect.GetX(), rect.GetY(), 0.0); break;
        }

        context.quadVertexDataPtr->position = position;
        context.quadVertexDataPtr->pixelColor = (Vector4)color;
        context.quadVertexDataPtr->textureCoords = Vector2();
        context.quadVertexDataPtr->textureShaderSlot = 0;
        context.quadVertexDataPtr++;
    }

    context.quadCount++;
}
void Renderer::DrawFilledQuad(Vector3 position, Vector3 size, Color color)
{
    DrawFilledQuad(Rect(position, size), color);
}
void Renderer::DrawFilledQuad(float x, float y, float width, float height, Color color)
{
    DrawFilledQuad(Rect(x, y, width, height), color);
}

void Renderer::DrawRotatedQuad(Rect rect, float radians, Color color)
{
    if(context.quadCount > context.MAX_QUADS)
        NextBatch();

    Vector4 position;
    for(int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0: position = Vector4(rect.GetX(), rect.GetYMax(), 0.0); break;
            case 1: position = Vector4(rect.GetXMax(), rect.GetYMax(), 0.0); break;
            case 2: position = Vector4(rect.GetXMax(), rect.GetY(), 0.0); break;
            case 3: position = Vector4(rect.GetX(), rect.GetY(), 0.0); break;
        }

        context.quadVertexDataPtr->position = Matrix4::Rotate(radians, Vector3::Forward) * position;
        context.quadVertexDataPtr->pixelColor = (Vector4)color;
        context.quadVertexDataPtr->textureCoords = Vector2();
        context.quadVertexDataPtr->textureShaderSlot = 0;
        context.quadVertexDataPtr++;
    }

    context.quadCount++;
}
void Renderer::DrawRotatedQuad(Vector3 position, Vector3 size, float radians, Color color)
{
    DrawRotatedQuad(Rect(position, size), radians, color);
}
void Renderer::DrawRotatedQuad(float x, float y, float width, float height, float radians, Color color)
{
    DrawRotatedQuad(Rect(x, y, width, height), radians, color);
}

void Renderer::DrawSprite(WeakPtr<Sprite> sprite, Matrix4 transform, Color color)
{
    if(context.quadCount > context.MAX_QUADS)
        NextBatch();

    if(context.currentTextureSlot >= GraphicsContext::GetMaxTextureSlots())
        NextBatch();

    if(sprite.expired())
        return;

    if(sprite.lock()->GetTexture().expired())
        return;
        
    Vector4 position;

    Rect rect = sprite.lock()->GetRect();
    Vector2* texCoords = sprite.lock()->GetTextureCoordinates();
    
    F32 textureSlot = GetTextureSlot(sprite.lock()->GetTexture());
    
    for(int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0: position = Vector4(rect.GetX(), rect.GetYMax(), 0.0); break;
            case 1: position = Vector4(rect.GetXMax(), rect.GetYMax(), 0.0); break;
            case 2: position = Vector4(rect.GetXMax(), rect.GetY(), 0.0); break;
            case 3: position = Vector4(rect.GetX(), rect.GetY(), 0.0); break;
        }

        context.quadVertexDataPtr->position = transform * position;
        context.quadVertexDataPtr->pixelColor = (Vector4)color;
        context.quadVertexDataPtr->textureCoords = texCoords[i];
        context.quadVertexDataPtr->textureShaderSlot = textureSlot;
        context.quadVertexDataPtr++;
    }

    context.quadCount++;
}
