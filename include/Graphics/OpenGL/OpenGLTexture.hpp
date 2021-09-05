#ifndef OPENGL_TEXTURE_HPP
#define OPENGL_TEXTURE_HPP

#include <string.h>

#include "GLEW/glew.h"
#include "stb_image/stb_image.h"

#include "Core/Common/Types.hpp"
#include "Core/Debug/Assert.hpp"
#include "Core/Logger/Logger.hpp"

namespace Scramble::Graphics
{
    class OpenGLTexture
    {
    private:
        U32 textureId;

    private:
        byte* data;
    
    private:
        U32 pitch;
        U32 width, height;

    public:
        OpenGLTexture(const char* filepath);
        OpenGLTexture(U32 width, U32 height, U32 color);

    public:
        ~OpenGLTexture();

    public:
        U32 GetNativeId() const;

    public:
        byte* GetRawData();
    
    public:
        U32 GetPitch() const;
        U32 GetWidth() const;
        U32 GetHeight() const;
        
    public:
        void Bind(U32 slot = 0) const;
        void UnBind() const;
    };  
}

#endif