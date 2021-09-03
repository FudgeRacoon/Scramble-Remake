#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "OpenGL/OpenGLTexture.hpp"

#include "Core/Common/Types.hpp"

namespace Scramble::Graphics
{
    class Texture
    {
    private:    
        U32* pixels;

    private:    
        U32 width; 
        U32 height;
        U32 channels;
    
    private:
        OpenGLTexture* nativeTexture;

    public:
        Texture(const char* filepath);
        Texture(U32 width, U32 height, U32 color);
        
    public:    
        ~Texture();

    public:
        const U32* GetPixels();
    
    public:
        U32 GetWidth();
        U32 GetHeight();
        U32 GetChannels();

    public:
        const OpenGLTexture* GetNativeTexture();
    };
}

#endif