#include "Graphics/Sprite.hpp"
using namespace Scramble::Graphics;

Sprite::Sprite(WeakPtr<Texture> texture)
{
    this->rect = Rect(-32.0, 32.0, 64.0, 64.0);
    this->texture = texture;
    this->textureCoordinates = new Vector2[4];

    this->textureCoordinates[0] = Vector2(1.0, 0.0);
    this->textureCoordinates[1] = Vector2(0.0, 0.0);
    this->textureCoordinates[2] = Vector2(0.0, 1.0);
    this->textureCoordinates[3] = Vector2(1.0, 1.0);
}
Sprite::Sprite(WeakPtr<Texture> texture, Rect rect)
{
    this->rect = rect;
    this->texture = texture;
    this->textureCoordinates = new Vector2[4];

    this->textureCoordinates[0] = Vector2(1.0, 0.0);
    this->textureCoordinates[1] = Vector2(0.0, 0.0);
    this->textureCoordinates[2] = Vector2(0.0, 1.0);
    this->textureCoordinates[3] = Vector2(1.0, 1.0);
}
Sprite::Sprite(WeakPtr<Texture> texture, Rect rect, Vector2* textureCoordinates)
{
    this->rect = rect;
    this->texture = texture;
    this->textureCoordinates = new Vector2[4];

    memcpy(this->textureCoordinates, textureCoordinates, 4 * sizeof(Vector2));
}

Sprite::~Sprite()
{
    delete[] this->textureCoordinates;
}

Rect Sprite::GetRect()
{
    return this->rect;
}
WeakPtr<Texture> Sprite::GetTexture()
{
    return this->texture;
}
Vector2* Sprite::GetTextureCoordinates()
{
    return this->textureCoordinates;
}

void Sprite::SetRect(Rect rect)
{
    this->rect = rect;
}
void Sprite::SetTexture(WeakPtr<Texture> texture)
{
    this->texture = texture;
}
void Sprite::SetTextureCoordinates(Vector2* textureCoordinates)
{   
    memcpy(this->textureCoordinates, textureCoordinates, 4 * sizeof(Vector2));
}