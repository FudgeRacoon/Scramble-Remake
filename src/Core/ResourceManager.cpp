#include "Core/ResourceManager.hpp"
using namespace Scramble;

ResourceManager::SpriteMap ResourceManager::sprites;

ResourceManager::FontMap ResourceManager::fonts;
ResourceManager::AudioMap ResourceManager::audio;
ResourceManager::ShaderMap ResourceManager::shaders;
ResourceManager::TextureMap ResourceManager::textures;

void ResourceManager::OnStartUp()
{
    S_INFO("ResourceManager is starting up...");

    Shader* defaultShader = new Shader("Assets\\Shaders\\DefaultVertexShader.shader", "Assets\\Shaders\\DefaultFragmentShader.shader");

    defaultShader->GetNativeShader()->Bind();
    
    for(int i = 0; i < GraphicsContext::GetMaxTextureSlots(); i++)
        defaultShader->SetInt(std::string("textures[" + std::to_string(i) + "]").c_str(), i);
    
    defaultShader->GetNativeShader()->UnBind();

    Texture* greenTexture = new Texture(64, 64, 0xff000ff00);
    Texture* whiteTexture = new Texture(64, 64, 0xffffffff);
    Texture* blackTexture = new Texture(64, 64, 0x000000ff);

    shaders.insert(
        std::make_pair(std::string("Default_Shader"), SharedPtr<Shader>(defaultShader, [](Shader* shader) {delete shader;}))  
    );
    textures.insert(
        std::make_pair(std::string("Green_Texture"), SharedPtr<Texture>(greenTexture, [](Texture* texture) {delete texture;}))
    );
    textures.insert(
        std::make_pair(std::string("White_Texture"), SharedPtr<Texture>(whiteTexture, [](Texture* texture) {delete texture;}))
    );
    textures.insert(
        std::make_pair(std::string("Black_Texture"), SharedPtr<Texture>(blackTexture, [](Texture* texture) {delete texture;}))
    );
}
void ResourceManager::OnShutDown()
{
    for(auto sprite : sprites)
        sprite.second.reset();

    for(auto shader : shaders)
        shader.second.reset();

    for(auto texture : textures)
        texture.second.reset();

    sprites.clear();
    shaders.clear();
    textures.clear();
}

void ResourceManager::CreateSprite(std::string name, WeakPtr<Texture> texture)
{
    auto it = sprites.find(name);

    if(it == sprites.end())
    {
        Sprite* sprite = new Sprite(texture);
        sprites.insert(
            std::make_pair(name, SharedPtr<Sprite>(sprite, [](Sprite* sprite) {delete sprite;}))
        );

        S_INFO("Sprite: %s has been created succesfully!", name.c_str());
        return;
    }

    S_WARN("Sprite already exists!");
}
void ResourceManager::CreateSprite(std::string name, WeakPtr<Texture> texture, Rect rect)
{
    auto it = sprites.find(name);

    if(it == sprites.end())
    {
        Sprite* sprite = new Sprite(texture, rect);
        sprites.insert(
            std::make_pair(name, SharedPtr<Sprite>(sprite, [](Sprite* sprite) {delete sprite;}))
        );

        S_INFO("Sprite: %s has been created succesfully!", name.c_str());
        return;
    }

    S_WARN("Sprite already exists!");
}
void ResourceManager::CreateSprite(std::string name, WeakPtr<Texture> texture, Vector2* uv)
{
    auto it = sprites.find(name);

    if(it == sprites.end())
    {
        Sprite* sprite = sprite = new Sprite(texture, Rect(-16.0, 16.0, 32.0, 32.0), uv);
        
        sprites.insert(
            std::make_pair(name, SharedPtr<Sprite>(sprite, [](Sprite* sprite) {delete sprite;}))
        );

        S_INFO("Sprite: %s has been created succesfully!", name.c_str());
        return;
    }

    S_WARN("Sprite already exists!");
}

void ResourceManager::CreateTexture(std::string name, U32 width, U32 height, U32 color)
{
    auto it = textures.find(name);

    if(it == textures.end())
    {
        Texture* texture = new Texture(width, height, color);
        textures.insert(
            std::make_pair(name, SharedPtr<Texture>(texture, [](Texture* texture) {delete texture;}))
        );

        S_INFO("Texture: %s has been loaded succesfully!", name.c_str());
        return;
    }

    S_WARN("Texture already exists!");
}

void ResourceManager::LoadFont(std::string name, Str filepath)
{

}
void ResourceManager::LoadAudio(std::string name, Str filepath)
{

}
void ResourceManager::LoadShader(std::string name, Str vertexPath, Str fargmentPath)
{
    auto it = shaders.find(name);

    if(it == shaders.end())
    {
        Shader* shader = new Shader(vertexPath, fargmentPath);
        shaders.insert(
            std::make_pair(name, SharedPtr<Shader>(shader, [](Shader* shader) {delete shader;}))
        );

        S_INFO("Shader: %s has been loaded succesfully!", name.c_str());
        return;
    }

    S_WARN("Shader already exists!");
}
void ResourceManager::LoadTexture(std::string name, Str filepath)
{
    auto it = textures.find(name);

    if(it == textures.end())
    {
        Texture* texture = new Texture(filepath);
        textures.insert(
            std::make_pair(name, SharedPtr<Texture>(texture, [](Texture* texture) {delete texture;}))
        );

        S_INFO("Texture: %s has been loaded succesfully!", name.c_str());
        return;
    }

    S_WARN("Texture already exists!");
}

WeakPtr<Sprite> ResourceManager::GetSprite(std::string name)
{
    auto it = sprites.find(name);
    
    if(it != sprites.end())
        return it->second;

    S_WARN("Sprite does not exist!");
}

WeakPtr<Font> ResourceManager::GetFont(std::string name)
{

}
WeakPtr<Audio> ResourceManager::GetAudio(std::string name)
{

}
WeakPtr<Texture> ResourceManager::GetTexture(std::string name)
{
    auto it = textures.find(name);
    
    if(it != textures.end())
        return it->second;

    S_WARN("Texture does not exist!");
}
WeakPtr<Shader> ResourceManager::GetShader(std::string name)
{
    auto it = shaders.find(name);
    
    if(it != shaders.end())
        return it->second;

    S_WARN("Shader does not exist!");
}

void ResourceManager::DestroySprite(std::string name)
{
    auto it = sprites.find(name);
    
    if(it != sprites.end())
    {
        it->second.reset();
        sprites.erase(it);

        S_INFO("Sprite: %s has been destroyed succesfully!", name.c_str());
        return;
    }

    S_WARN("Sprite does not exist!");
}

void ResourceManager::DestroyFont(std::string name)
{

}
void ResourceManager::DestroyAudio(std::string name)
{

}
void ResourceManager::DestroyShader(std::string name)
{
    auto it = shaders.find(name);
    
    if(it != shaders.end())
    {
        it->second.reset();
        shaders.erase(it);

        S_INFO("Shader: %s has been destroyed succesfully!", name.c_str());
        return;
    }

    S_WARN("Shader does not exist!");
}
void ResourceManager::DestroyTexture(std::string name)
{
    auto it = textures.find(name);
    
    if(it != textures.end())
    {
        it->second.reset();
        textures.erase(it);

        S_INFO("Texture: %s has been destroyed succesfully!", name.c_str());
        return;
    }

    S_WARN("Texture does not exist!");
}