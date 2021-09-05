#include "Utils/SpriteUtils.hpp"
using namespace Scramble::Utils;

void SpriteUtils::SliceSprite(WeakPtr<Sprite> sprite, std::string name, I32 spriteWidth, I32 spriteHeight)
{
    I32 counter = 0;

    F32 width = sprite.lock()->GetTexture().lock()->GetWidth();
    F32 height = sprite.lock()->GetTexture().lock()->GetHeight();

    I32 horzI32alNumOfSprites = width / spriteWidth;
    I32 verticalNumOfSprites = height / spriteHeight;
    
    Vector2 texCoords[4];

    for(I32 y = 1; y <= verticalNumOfSprites; y++)
        for(I32 x = 0; x < horzI32alNumOfSprites; x++)
        {
            F32 currentWidth = spriteWidth * x;
            F32 currentHeight = spriteHeight * y;

            F32 xBottom = currentWidth / width;
            F32 yBottom = (height - currentHeight) / height;

            F32 xTop = (currentWidth + spriteWidth) / width;
            F32 yTop = ((height - currentHeight) + spriteHeight) / height;

            texCoords[0] = Vector2(xTop, yBottom);
            texCoords[1] = Vector2(xBottom, yBottom);
            texCoords[2] = Vector2(xBottom, yTop);
            texCoords[3] = Vector2(xTop, yTop);

            std::string spriteName = name + "_" + std::to_string(counter++);

            ResourceManager::CreateSprite(spriteName, sprite.lock()->GetTexture(), texCoords);
        }

}