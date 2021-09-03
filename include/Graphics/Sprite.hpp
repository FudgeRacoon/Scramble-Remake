#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string.h>

#include "Core/Geometry/Rect.hpp"
#include "Core/Math/Vector2.hpp"
#include "Core/Math/Vector2.hpp"

#include "Graphics/Texture.hpp"
using namespace Scramble;

namespace Scramble::Graphics
{   
    class Sprite
    {
    private:
        Rect rect;
        Texture* texture;
        Vector2* textureCoords;

    public:
        Sprite(Texture* texture);
        Sprite(Texture* texture, Rect rect);
        Sprite(Texture* texture, Rect rect, Vector2* textureCoords);
    
    public:
        ~Sprite();

    public:
        Rect GetRect();
        Texture* GetTexture();
        Vector2* GetTextureCoords();

    public:
        void SetRect(Rect rect);
        void SetTexture(Texture* texture);
        void SetTextureCoords(Vector2* textureCoords);
    };
}

#endif