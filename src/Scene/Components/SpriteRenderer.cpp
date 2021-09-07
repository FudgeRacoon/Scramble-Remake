#include "Scene/Components/SpriteRenderer.hpp"
using namespace Scramble::Scene;

SpriteRenderer::SpriteRenderer(Entity* owner) : Component(owner)
{
    this->flipX = false;
    this->flipY = false;
    this->sortingOrder = 0;
}
SpriteRenderer::SpriteRenderer(Entity* owner, WeakPtr<Sprite> sprite) : Component(owner)
{   
    this->sprite = sprite;
    
    this->flipX = false;
    this->flipY = false;
    this->sortingOrder = 0;
}

void SpriteRenderer::Setup() {}
void SpriteRenderer::Update() {}