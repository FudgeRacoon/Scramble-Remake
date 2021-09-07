#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string.h>

#include "Core/Common/Types.hpp"
#include "Core/Geometry/Rect.hpp"
#include "Core/Math/Vector2.hpp"
#include "Core/Math/Vector2.hpp"

#include "Graphics/Texture.hpp"
using namespace Scramble;

namespace Scamble
{
    class ResourceManager;
}

namespace Scramble::Graphics
{   
    class Sprite
    {
    private:
        Rect rect;
        WeakPtr<Texture> texture;
        Vector2* textureCoordinates;

    private:
        U32 width, height;

    private:
        Sprite(std::weak_ptr<Texture> texture);
        Sprite(std::weak_ptr<Texture> texture, Rect rect);
        Sprite(std::weak_ptr<Texture> texture, Rect rect, Vector2* textureCoordinates, U32 width = 0, U32 height = 0);
    
    private:
        ~Sprite();

    public:
        Rect GetRect();
        WeakPtr<Texture> GetTexture();
        Vector2* GetTextureCoordinates();

    public:
        U32 GetWidth();
        U32 GetHeight();

    public:
        void SetRect(Rect rect);
        void SetTexture(WeakPtr<Texture> texture);
        void SetTextureCoordinates(Vector2* textureCoordinates);

    friend ResourceManager;
    };
}

#endif