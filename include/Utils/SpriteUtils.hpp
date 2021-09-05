#ifndef SPRITE_UTILS_HPP
#define SPRITE_UTILS_HPP

#include <string>

#include "Core/Common/Types.hpp"
#include "Core/ResourceManager.hpp"

#include "Graphics/Sprite.hpp"
using namespace Scramble::Graphics;

namespace Scramble::Utils
{
    class SpriteUtils
    {
    private:
        SpriteUtils() = delete;
        ~SpriteUtils() = delete;

    public:
        static void SliceSprite(WeakPtr<Sprite> sprite, std::string name, I32 spriteWidth, I32 spriteHeight);
    };
}

#endif