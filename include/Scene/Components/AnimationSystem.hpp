#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include "Core/Common/Types.hpp"
#include "Core/Time/Time.hpp"

#include "Graphics/Sprite.hpp"

#include "../Entity.hpp"
#include "../Component.hpp"
#include "SpriteRenderer.hpp"

using namespace Scramble;
using namespace Scramble::Graphics;

namespace Scramble::Scene
{
    class AnimationSystem : public Component
    {
    private:    
        I32 keyFrames;
        I32 currentKeyFrame;
        F32 sampleRate;
        F32 previousFrame;

    private:
        SpriteRenderer* spriteRenderer;

    private:
        WeakPtr<Sprite>* sprites;

    public:
        AnimationSystem(Entity* entity, I32 keyFrames, F32 sampleRate);

    public:
        void AddSprites(WeakPtr<Sprite>* sprites);

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif