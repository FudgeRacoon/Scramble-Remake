#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "RendererContext.hpp"

namespace Scramble::Graphics
{
    class Renderer
    {
    private:
        static RendererContext context;

    private:
        static void StartBatch();
        static void EndBatch();
        static void Flush();

    public:
        static void InitBuffers();
        static void InitShaders();
        static void InitTextures();

    public:
        void OnStartUp();
        void OnShutDown();
    };
}

#endif