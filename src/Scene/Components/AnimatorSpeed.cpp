#include "Scene/Components/AnimationSystem.hpp"
using namespace Scramble::Scene;

AnimationSystem::AnimationSystem(Entity* entity, I32 keyFrames, F32 sampleRate) : Component(entity)
{
    this->keyFrames = keyFrames;
    this->sampleRate = sampleRate;
    this->currentKeyFrame = -1;
    this->previousFrame = 0.0f;

    this->sprites = new WeakPtr<Sprite>[keyFrames];

    this->spriteRenderer = owner->GetComponent<SpriteRenderer>();
}

void AnimationSystem::AddSprites(WeakPtr<Sprite>* sprites)
{
    this->sprites = sprites;
}

void AnimationSystem::Setup()
{

}
void AnimationSystem::Update()
{
    if(Time::GetElapsedTime() >= sampleRate + previousFrame)
    {
        previousFrame = Time::GetElapsedTime();
        currentKeyFrame = (currentKeyFrame + 1) % keyFrames;
        spriteRenderer->sprite = sprites[currentKeyFrame];
    }
}