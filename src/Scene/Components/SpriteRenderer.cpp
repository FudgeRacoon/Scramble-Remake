#include "Scene/Components/SpriteRenderer.hpp"
using namespace Scramble::Scene;

SpriteRenderer::SpriteRenderer()
    : flipX(false), flipY(false), sortingOrder(0) {}
SpriteRenderer::SpriteRenderer(WeakPtr<Sprite> sprite)
    : sprite(sprite), flipX(false), flipY(false), sortingOrder(0) {}

void SpriteRenderer::Setup() {}
void SpriteRenderer::Update() {}