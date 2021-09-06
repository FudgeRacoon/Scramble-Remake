#ifndef RUNTIME_SCENE_MANAGER_HPP
#define RUNTIME_SCENE_MANAGER_HPP

#include <vector>

#include "Core/Common/Types.hpp"
#include "Core/Debug/Assert.hpp"
#include "Core/Logger/Logger.hpp"

#include "Camera.hpp"
#include "RuntimeScene.hpp"

namespace Scramble::Scene
{
    class RuntimeSceneManager
    {
    typedef std::vector<SharedPtr<RuntimeScene>> SceneArray;

    private:
        static SceneArray runtimeScenes;
        static SharedPtr<RuntimeScene> activeScene;

    private:
        RuntimeSceneManager() = delete;

    public:
        static WeakPtr<RuntimeScene> GetActiveScene();

    public:
        static void CreateScene(std::string name);
        static void RemoveScene(U32 buildIndex);
        static void ChangeActiveScene(U32 buildIndex);
        static void UpdateActiveScene();
    };

    #define GetActiveCamera() RuntimeSceneManager::GetActiveScene().lock()->GetSceneCamera()
    
    #define CreateEntity() RuntimeSceneManager::GetActiveScene().lock()->AddEntity()
    #define CreateEntity(name) RuntimeSceneManager::GetActiveScene().lock()->AddEntity(#name)
    #define CreateEntity(position, rotation, scale) RuntimeSceneManager::GetActiveScene().lock()->AddEntity(position, rotation, scale)
    #define CreateEntity(name, position, rotation, scale) RuntimeSceneManager::GetActiveScene().lock()->AddEntity(#name, position, rotation, scale)

    #define FindEntityById(id) RuntimeSceneManager::GetActiveScene().lock()->GetEntityById(id)
    #define FindEntityByTag(tag) RuntimeSceneManager::GetActiveScene().lock()->GetEntityById(#tag)

    #define DestroyEntityById(id) RuntimeSceneManager::GetActiveScene().lock()->DestroyEntityById(id)
    #define DestroyEntityByTag(tag) RuntimeSceneManager::GetActiveScene().lock()->DestroyEntityByTag(#tag)
}

#endif