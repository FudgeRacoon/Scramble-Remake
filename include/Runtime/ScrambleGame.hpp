#ifndef SCRAMBLEGAME_HPP
#define SCRAMBLEGAME_HPP

#include "Scramble.hpp"
using namespace Scramble::Graphics;
using namespace Scramble::Input;
using namespace Scramble::Scene;
using namespace Scramble::Utils;

void Internal_InitTestScene()
{
    RuntimeSceneManager::CreateScene("Test_Scene");
    RuntimeSceneManager::ChangeActiveScene(0);

    auto entity = CreateEntity("Karim", Vector3(100.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.8), Vector3(1.0, 1.0, 1.0));

    entity.lock()->AddComponent<SpriteRenderer>(ResourceManager::GetSprite("SpaceShip_0"));
}

namespace Scramble
{
    class ScrambleGame : public RuntimeInstance
    {
    public:
        void OnEnter() override
        {   
            ResourceManager::LoadTexture("SpaceShip_SpriteSheet_Texture", "assets\\textures\\SpaceShipSheet.png");
            ResourceManager::CreateSprite("SpaceShip_SpriteSheet", ResourceManager::GetTexture("SpaceShip_SpriteSheet_Texture"));
            SpriteUtils::SliceSprite(ResourceManager::GetSprite("SpaceShip_SpriteSheet"), "SpaceShip", 32, 32);

            Internal_InitTestScene();
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