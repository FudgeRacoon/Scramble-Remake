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
            ResourceManager::CreateSprite("LaserShot", ResourceManager::GetTexture("Green_Texture"));
            ResourceManager::CreateSprite("SpaceShip_SpriteSheet", ResourceManager::GetTexture("SpaceShip_SpriteSheet_Texture"));

            SpriteUtils::SliceSprite(ResourceManager::GetSprite("SpaceShip_SpriteSheet"), "SpaceShip", 32, 32);
            
            WeakPtr<Sprite>* sprites = new WeakPtr<Sprite>[4];
            sprites[0] = ResourceManager::GetSprite("SpaceShip_0");
            sprites[1] = ResourceManager::GetSprite("SpaceShip_1");
            sprites[2] = ResourceManager::GetSprite("SpaceShip_2");
            sprites[3] = ResourceManager::GetSprite("SpaceShip_3");

            RuntimeSceneManager::CreateScene("Level_1");
            RuntimeSceneManager::ChangeActiveScene(0);

            auto entity = CreateEntity("SpaceShip", Vector3(), Vector3(), Vector3(1.5f, 1.5f, 1.0));
            entity.lock()->AddComponent<SpriteRenderer>(ResourceManager::GetSprite("SpaceShip_0"));
            entity.lock()->AddComponent<AnimationSystem>(4, 0.1f)->AddSprites(sprites);
            entity.lock()->AddComponent<RigidBody>(BodyType::DYNAMIC);
            entity.lock()->AddComponent<BoxCollider>(Vector3(32.0f, 32.0f, 0.0f));
            entity.lock()->AddComponent<PlayerController>();
        }   

        void OnUpdate() override
        {
           RuntimeSceneManager::UpdateActiveScene();
        }
    };
}

#endif