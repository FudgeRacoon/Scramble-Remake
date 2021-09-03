#include "Graphics/Sprite.hpp"
using namespace Scramble::Graphics;

Sprite::Sprite(Texture* texture)
{
    this->rect = Rect(-32.0, 32.0, 64.0, 64.0);
    this->texture = texture;
    this->textureCoords = new Vector2[4];

    this->textureCoords[0] = Vector2(0.0, 0.0);
    this->textureCoords[1] = Vector2(1.0, 0.0);
    this->textureCoords[2] = Vector2(1.0, 1.0);
    this->textureCoords[3] = Vector2(0.0, 1.0);
}
Sprite::Sprite(Texture* texture, Rect rect)
{
    this->rect = rect;
    this->texture = texture;
    this->textureCoords = new Vector2[4];

    this->textureCoords[0] = Vector2(0.0, 0.0);
    this->textureCoords[1] = Vector2(1.0, 0.0);
    this->textureCoords[2] = Vector2(1.0, 1.0);
    this->textureCoords[3] = Vector2(0.0, 1.0);
}
Sprite::Sprite(Texture* texture, Rect rect, Vector2* textureCoords)
{
    this->rect = rect;
    this->texture = texture;
    this->textureCoords = new Vector2[4];

    memcpy(this->textureCoords, textureCoords, 4 * sizeof(Vector2));
}

Sprite::~Sprite()
{
    delete[] this->textureCoords;
}

Rect Sprite::GetRect()
{
    return this->rect;
}
Texture* Sprite::GetTexture()
{
    return this->texture;
}
Vector2* Sprite::GetTextureCoords()
{
    return this->textureCoords;
}

void Sprite::SetRect(Rect rect)
{
    this->rect = rect;
}
void Sprite::SetTexture(Texture* texture)
{
    this->texture = texture;
}
void Sprite::SetTextureCoords(Vector2* textureCoords)
{   
    memcpy(this->textureCoords, textureCoords, 4 * sizeof(Vector2));
}