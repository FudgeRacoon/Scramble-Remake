#ifndef SCRAMBLEGAME_HPP
#define SCRAMBLEGAME_HPP

#include "Scramble.hpp"
using namespace Scramble::Graphics;
using namespace Scramble::Input;
using namespace Scramble::Scene;
using namespace Scramble::Utils;

#include "PlayerController.hpp"

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

            SpriteUtils::SliceSprite(ResourceManager::GetSprite("SpaceShip_SpriteSheet"), "SpaceShip", 32, 32);

            RuntimeSceneManager::CreateScene("Scene_0");
            RuntimeSceneManager::ChangeActiveScene(0);

            auto entity = CreateEntity("SpaceShip");
            entity.lock()->AddComponent<SpriteRenderer>(ResourceManager::GetSprite("SpaceShip_0"));
            entity.lock()->AddComponent<RigidBody>(BodyType::DYNAMIC);
            entity.lock()->AddComponent<BoxCollider>(Vector3(50.0f, 32.0f, 0.0f));
            entity.lock()->AddComponent<PlayerController>();
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