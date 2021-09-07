#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Core/Common/Types.hpp"

#include "OpenGL/OpenGLTexture.hpp"

namespace Scramble
{
    class ResourceManager;
}

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

    private:
        Texture(const char* filepath);
        Texture(U32 width, U32 height, U32 color);
        
    private:    
        ~Texture();

    public:
        bool operator ==(Texture texture);
        bool operator !=(Texture texture);

    public:
        const U32* GetPixels();
    
    public:
        U32 GetWidth();
        U32 GetHeight();
        U32 GetChannels();

    public:
        const OpenGLTexture* GetNativeTexture();

    friend ResourceManager;
    };
}

#endif