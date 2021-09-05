#ifndef SCRAMBLEGAME_HPP
#define SCRAMBLEGAME_HPP

#include "Scramble.hpp"
using namespace Scramble::Graphics;
using namespace Scramble::Input;
using namespace Scramble::Utils;

namespace Scramble
{
    class ScrambleGame : public RuntimeInstance
    {
    private:
        Camera* mainCamera;
        Vector3 position;

        F32 frameTime;
        F32 previousFrameTime;
        I32 currentFrameIndex;
        WeakPtr<Sprite> currentFrame;
        WeakPtr<Sprite> spriteFrames[4];

    public:
        void OnEnter() override
        {   
            mainCamera = new Camera();

            ResourceManager::LoadTexture("SpaceShip_SpriteSheet_Texture", "assets\\textures\\SpaceShipSheet.png");
            ResourceManager::CreateSprite("SpaceShip_SpriteSheet", ResourceManager::GetTexture("SpaceShip_SpriteSheet_Texture"));

            SpriteUtils::SliceSprite(ResourceManager::GetSprite("SpaceShip_SpriteSheet"), "SpaceShip", 32, 32);

            frameTime = 0.075;
            previousFrameTime = 0.0;
            currentFrameIndex = -1;
            spriteFrames[0] = ResourceManager::GetSprite("SpaceShip_0");
            spriteFrames[1] = ResourceManager::GetSprite("SpaceShip_1");
            spriteFrames[2] = ResourceManager::GetSprite("SpaceShip_2");
            spriteFrames[3] = ResourceManager::GetSprite("SpaceShip_3");
        
            position += Vector3(200, 0, 0);
        }   

        void OnUpdate() override
        {
            if(InputManager::GetKey(KeyCode::KEY_RIGHT))
                position += Vector3(200, 0, 0) * Time::GetDeltaTime();
            if(InputManager::GetKey(KeyCode::KEY_LEFT))
                position += Vector3(-200, 0, 0) * Time::GetDeltaTime();
            if(InputManager::GetKey(KeyCode::KEY_UP))
                position += Vector3::Up * 200.0 * Time::GetDeltaTime();
            if(InputManager::GetKey(KeyCode::KEY_DOWN))
                position += Vector3::Down * 200.0 * Time::GetDeltaTime();

            if(Time::GetElapsedUnscaledTime() >= frameTime + previousFrameTime)
            {   
                previousFrameTime = Time::GetElapsedUnscaledTime();
                currentFrameIndex = (currentFrameIndex + 1) % 4;
                currentFrame = spriteFrames[currentFrameIndex];
            }            
            
            Renderer::BeginScene(mainCamera);

            Renderer::DrawSprite(currentFrame, Matrix4::Transalte(position), Color::white);

            Renderer::EndScene();
        }

        void OnExit() override
        {

        }
    };
}

#endif