#include "Graphics/OpenGL/OpenGLTexture.hpp"
using namespace Scramble::Graphics;

OpenGLTexture::OpenGLTexture(const char* filepath)
{
    int width, height, channels;
    
    this->data = stbi_load(filepath, &width, &height, &channels, 0);
    
    SCRAMBLE_CORE_ASSERT_LOG(this->data, "Failed to load image");

    this->width = width;
    this->height = height;
    this->pitch = channels * width;

    byte* topData = this->data;
    byte* bottomData = this->data + ((this->height - 1) * this->pitch);

    for(int y = 0; y < this->height / 2; y++)
    {
        byte* tempTopBuffer = new byte[this->pitch];
        byte* tempBottomBuffer = new byte[this->pitch];

        memcpy(tempTopBuffer, topData, this->pitch);
        memcpy(tempBottomBuffer, bottomData, this->pitch);

        memcpy(topData, tempBottomBuffer, this->pitch);
        memcpy(bottomData, tempTopBuffer, this->pitch);

        topData += this->pitch;
        bottomData -= this->pitch;

        delete[] tempTopBuffer;
        delete[] tempBottomBuffer;
    }

    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, this->data);

    glBindTexture(GL_TEXTURE_2D, 0);
}
OpenGLTexture::OpenGLTexture(U32 width, U32 height, U32 color)
{
    this->width = width;
    this->height = height;
    this->pitch = width * 4;

    this->data = new byte[this->height * this->pitch];
    for(int y = 0; y < this->height; y++)
        for(int x = 0; x < this->pitch; x += 4)
            {
                byte* ptr = &(this->data[(y * this->pitch) + x]);
                
                int len = 0;
                int shamt = 24;
                while(len < 4)
                {
                    *ptr = color >> shamt;
                    shamt -= 8;
                    ptr++;
                    len++;
                }
            } 

    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, this->data);

    glBindTexture(GL_TEXTURE_2D, 0);
}
OpenGLTexture::~OpenGLTexture()
{
    delete[] this->data;

    glDeleteTextures(1, &this->textureId);
}

U32 OpenGLTexture::GetNativeId() const
{
    return this->textureId;
}

byte* OpenGLTexture::GetRawData()
{
    return this->data;
}

U32 OpenGLTexture::GetPitch() const
{
    return this->pitch;
}
U32 OpenGLTexture::GetWidth() const
{
    return this->width;
}
U32 OpenGLTexture::GetHeight() const
{
    return this->height;
}

void OpenGLTexture::Bind(U32 slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
}
void OpenGLTexture::UnBind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}