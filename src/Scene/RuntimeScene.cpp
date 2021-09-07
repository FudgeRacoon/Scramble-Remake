#include "Scene/RuntimeScene.hpp"
using namespace Scramble::Scene;

RuntimeScene::RuntimeScene(std::string sceneName, SharedPtr<Camera> sceneCamera)
{
    this->sceneName = sceneName;
    this->sceneCamera = sceneCamera;
    this->sceneRegistry = UniquePtr<Registry>(new Registry());
}

RuntimeScene::~RuntimeScene()
{
    this->sceneCamera.reset();
    this->sceneRegistry->Release();
    this->sceneRegistry.reset();
}

void RuntimeScene::Internal_RenderEntity(Transform* transform, SpriteRenderer* spriteRenderer)
{
    if(spriteRenderer)
    {
        Matrix4 transformMatrix = Matrix4::Transform(
            transform->position,
            transform->rotation,
            transform->scale
        );

        Renderer::DrawSprite(
            spriteRenderer->sprite,
            transformMatrix,
            spriteRenderer->spriteColor
        );
    }
}

void RuntimeScene::OnSetupRuntime()
{
    this->sceneRegistry->PollSetupQueue();
}
void RuntimeScene::OnUpdateRuntime()
{
    Renderer::BeginScene(this->sceneCamera);
    
    this->sceneRegistry->ForEach([] (SharedPtr<Entity> entity)
        {
            if(entity->GetComponent<Tag>()->enabled)
            {
                entity->Update();
                
                Transform* transform = entity->GetComponent<Transform>();
                SpriteRenderer* spriteRenderer = entity->GetComponent<SpriteRenderer>();
                Internal_RenderEntity(transform, spriteRenderer);
            }
        }
    );

    this->sceneRegistry->PollDestroyQueue();  

    Renderer::EndScene();
}
void RuntimeScene::OnExitRuntime()
{
    this->sceneRegistry->ResetSetupQueue();
}

WeakPtr<Camera> RuntimeScene::GetSceneCamera()
{
    return this->sceneCamera;
}

WeakPtr<Entity> RuntimeScene::AddEntity()
{
    return this->sceneRegistry->AddEntity();
}
WeakPtr<Entity> RuntimeScene::AddEntity(std::string tag)
{
    return this->sceneRegistry->AddEntity(tag);
}
WeakPtr<Entity> RuntimeScene::AddEntity(Vector3 position, Vector3 rotation, Vector3 scale)
{
    return this->sceneRegistry->AddEntity(position, rotation, scale);
}
WeakPtr<Entity> RuntimeScene::AddEntity(std::string tag, Vector3 position, Vector3 rotation, Vector3 scale)
{
    return this->sceneRegistry->AddEntity(tag, position, rotation, scale);
}

WeakPtr<Entity> RuntimeScene::GetEntityById(U32 id)
{
    return this->sceneRegistry->GetEntityById(id);
}
WeakPtr<Entity> RuntimeScene::GetEntityByTag(std::string tag)
{
    return this->sceneRegistry->GetEntityByTag(tag);
}

void RuntimeScene::DestroyEntityById(U32 id)
{
    this->sceneRegistry->DestroyEntityById(id);
}
void RuntimeScene::DestroyEntityByTag(std::string tag)
{   
    this->sceneRegistry->DestroyEntityByTag(tag);
}
