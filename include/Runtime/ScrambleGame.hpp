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

            SpriteUtils::SliceSprite(ResourceManager::GetSprite("SpaceShip_SpriteSheet"), "SpaceShip", 32, 32);

            RuntimeSceneManager::CreateScene("Scene_0");
            RuntimeSceneManager::ChangeActiveScene(0);

            Vector3 pos(0.0, -250.0, 0.0);
            Vector3 scale(10, 1.0, 1.0);
            ground = CreateEntity("Ground", pos, Vector3(), scale);
            ground.lock()->AddComponent<RigidBody>(BodyType::STATIC, 0.0);

            ground.lock()->GetComponent<BoxCollider>()->SetSize(Vector3(640.0, 64.0, 1.0));
        }   

        void OnUpdate() override
        {
            if(InputManager::GetKeyDown(KeyCode::KEY_SPACE))
            {
                Vector3 positon(0.0, 0.0, 0.0);

                auto entity = CreateEntity(positon, Vector3(0.0, 0.0, 0.0), Vector3(1.0, 1.0, 1.0));
                entity.lock()->AddComponent<SpriteRenderer>(ResourceManager::GetSprite("SpaceShip_0"));
                entity.lock()->AddComponent<RigidBody>();
            }

           RuntimeSceneManager::UpdateActiveScene();
        }

        void OnExit() override
        {

        }
    };
}

#endif