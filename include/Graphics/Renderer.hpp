#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Core/ResourceManager.hpp"

#include "RendererContext.hpp"

namespace Scramble::Graphics
{
    class Renderer
    {
    private:
        static RendererContext context;

    private:
        static void StartBatch();
        static void NextBatch();
        static void Flush();

    private:
        static U32 GetTextureSlot(WeakPtr<Texture> texture); 

    private:
        Renderer() = delete;

    public:
        static void InitBuffers();
        static void InitShaders();
        static void InitTextures();

    public:
        static void OnStartUp();
        static void OnShutDown();

    public:
        static void BeginScene(SharedPtr<Camera> camera);
        static void EndScene();

    public:
        static WeakPtr<Shader> GetRegisteredShader();
        static void RegisterShader(WeakPtr<Shader> shader);

    public:
        static void DrawLine(Line line, Color color);
        static void DrawLine(Vector3 start, Vector3 end, Color color);
        static void DrawLine(float x0, float y0, float x1, float y1, Color color);

    public:
        static void DrawQuad(Rect rect, Color color);
        static void DrawQuad(Vector3 position, Vector3 size, Color color);
        static void DrawQuad(float x, float y, float width, float height, Color color);

    public:
        static void DrawFilledQuad(Rect rect, Color color);
        static void DrawFilledQuad(Vector3 position, Vector3 size, Color color);
        static void DrawFilledQuad(float x, float y, float width, float height, Color color);

    public:
        static void DrawRotatedQuad(Rect rect, float radians, Color color);
        static void DrawRotatedQuad(Vector3 position, Vector3 size, float radians, Color color);
        static void DrawRotatedQuad(float x, float y, float width, float height, float radians, Color color);

    public:
        static void DrawSprite(WeakPtr<Sprite> sprite, Matrix4 transform, Color color);
    };
}

#endif