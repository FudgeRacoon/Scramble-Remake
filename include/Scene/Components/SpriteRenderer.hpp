#ifndef SPRITE_RENDERER_COMPONENT_HPP
#define SPRITE_RENDERER_COMPONENT_HPP

#include "Core/Common/Types.hpp"
#include "Core/Math/Color.hpp"

#include "Graphics/Sprite.hpp"

#include "../Component.hpp"
using namespace Scramble::Graphics;

namespace Scramble::Scene
{
    class SpriteRenderer : public Component
    {
    public:
        WeakPtr<Sprite> sprite;
        Color spriteColor;

    public:
        bool flipX, flipY;
        U32 sortingOrder;

    public:
        SpriteRenderer();
        SpriteRenderer(WeakPtr<Sprite> sprite);

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif