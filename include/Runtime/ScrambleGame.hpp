#ifndef SCRAMBLEGAME_HPP
#define SCRAMBLEGAME_HPP

#include "Scramble.hpp"
using namespace Scramble::Graphics;
using namespace Scramble::Input;
using namespace Scramble::Scene;
using namespace Scramble::Utils;

namespace Scramble
{
    class ScrambleGame : public RuntimeInstance
    {
    private:
        WeakPtr<Entity> ground;

    public:
        void OnEnter() override
        {   
            ResourceManager::LoadTexture("SpaceShip_SpriteSheet_Texture", "assets\\textures\\SpaceShipSheet.png");
            ResourceManager::CreateSprite("SpaceShip_SpriteSheet", ResourceManager::GetTexture("SpaceShip_SpriteSheet_Texture"));
            ResourceManager::CreateSprite("Ground", ResourceManager::GetTexture("White_Texture"));
        }   

        void OnUpdate() override
        {
           RuntimeSceneManager::UpdateActiveScene();
        }

        void OnExit() override
        {

        }
    };
}

#endif