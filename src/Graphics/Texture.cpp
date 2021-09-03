#include "Graphics/Texture.hpp"
using namespace Scramble::Graphics;

Texture::Texture(const char* filepath)
{
    this->nativeTexture = new OpenGLTexture(filepath);

    this->pixels = (U32*)this->nativeTexture->GetRawData();

    this->channels = this->nativeTexture->GetPitch();
    this->width = this->nativeTexture->GetWidth();
    this->height = this->nativeTexture->GetHeight();
}
Texture::Texture(U32 width, U32 height, U32 color)
{
    this->nativeTexture = new OpenGLTexture(width, height, color);

    this->pixels = (U32*)this->nativeTexture->GetRawData();

    this->channels = this->nativeTexture->GetPitch();
    this->width = this->nativeTexture->GetWidth();
    this->height = this->nativeTexture->GetHeight();
}

Texture::~Texture()
{
    delete this->nativeTexture;
}

const U32* Texture::GetPixels()
{
    return this->pixels;
}

U32 Texture::GetWidth()
{
    return this->width;
}
U32 Texture::GetHeight()
{
    return this->height;
}
U32 Texture::GetChannels()
{
    return this->channels;
}

const OpenGLTexture* Texture::GetNativeTexture()
{
    return this->nativeTexture;
}
