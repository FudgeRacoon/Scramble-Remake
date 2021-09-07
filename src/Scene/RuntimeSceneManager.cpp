#include "Scene/RuntimeSceneManager.hpp"
using namespace Scramble::Scene;

RuntimeSceneManager::SceneArray RuntimeSceneManager::runtimeScenes;
SharedPtr<RuntimeScene> RuntimeSceneManager::activeScene;

WeakPtr<RuntimeScene> RuntimeSceneManager::GetActiveScene()
{
    SCRAMBLE_CORE_ASSERT_LOG(activeScene, "There is no active scene!");
    return activeScene;
}

void RuntimeSceneManager::CreateScene(std::string name)
{
    SharedPtr<Camera> camera(new Camera());

    runtimeScenes.push_back(
        SharedPtr<RuntimeScene>(new RuntimeScene(name, camera), [] (RuntimeScene* s) {delete s;})
    );

    S_INFO("Scene: %s has been created succesfully!", name.c_str());
}
void RuntimeSceneManager::RemoveScene(U32 buildIndex)
{
    SCRAMBLE_CORE_ASSERT_LOG(buildIndex < runtimeScenes.size() | buildIndex >= 0, "Build index is out of range!");
    SCRAMBLE_CORE_ASSERT_LOG(runtimeScenes[buildIndex] != activeScene, "Cannot remove active scene!");

    I32 counter = 0;
    auto it = runtimeScenes.begin();

    while(counter < buildIndex)
    {
        if(counter == buildIndex)
            runtimeScenes.erase(it + buildIndex);

        counter++;
    }

    S_INFO("Scene of build index: %d has been removed succesfully!", buildIndex);
}
void RuntimeSceneManager::ChangeActiveScene(U32 buildIndex)
{
    SCRAMBLE_CORE_ASSERT_LOG(buildIndex < runtimeScenes.size() | buildIndex >= 0, "Build index is out of range!");
    SCRAMBLE_CORE_ASSERT_LOG(runtimeScenes[buildIndex] != activeScene, "Scene already active!");

    if(activeScene)
        activeScene->OnExitRuntime();
    
    activeScene = runtimeScenes[buildIndex];

    S_INFO("Scene of build index: %d is now active!", buildIndex);
}
void RuntimeSceneManager::UpdateActiveScene()
{
    SCRAMBLE_CORE_ASSERT_LOG(activeScene != nullptr, "No active scene to update!");

    activeScene->OnSetupRuntime();
    activeScene->OnUpdateRuntime();
}