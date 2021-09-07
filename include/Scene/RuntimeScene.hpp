#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>

#include "Core/Common/Types.hpp"

#include "Graphics/Renderer.hpp"

#include "Components/Tag.hpp"
#include "Components/Transform.hpp"
#include "Components/SpriteRenderer.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

namespace Scramble::Scene
{
    class RuntimeSceneManager;

    class RuntimeScene
    {
    private:
        std::string sceneName;
        SharedPtr<Camera> sceneCamera;
        UniquePtr<Registry> sceneRegistry;

    private:
        RuntimeScene(std::string sceneName, SharedPtr<Camera> sceneCamera);

    private:
        ~RuntimeScene();

    private:
        static void Internal_RenderEntity(Transform* transform, SpriteRenderer* spriteRenderer);

    public:
        void OnSetupRuntime();
        void OnUpdateRuntime();
        void OnExitRuntime();

    public:
        SharedPtr<Camera> GetSceneCamera();

    public:
        WeakPtr<Entity> AddEntity();
        WeakPtr<Entity> AddEntity(std::string tag);
        WeakPtr<Entity> AddEntity(Vector3 position, Vector3 rotation, Vector3 scale);
        WeakPtr<Entity> AddEntity(std::string tag, Vector3 position, Vector3 rotation, Vector3 scale);

    public:
        WeakPtr<Entity> GetEntityById(U32 id);
        WeakPtr<Entity> GetEntityByTag(std::string tag);
    
    public:
        void DestroyEntityById(U32 id);
        void DestroyEntityByTag(std::string tag);

    friend RuntimeSceneManager;
    };
}

#endif