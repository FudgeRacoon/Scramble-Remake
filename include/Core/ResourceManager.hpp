#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>
#include <memory>

#include "Common/Types.hpp"
#include "Geometry/Rect.hpp"
#include "Math/Vector2.hpp"
#include "Debug/Assert.hpp"
#include "Logger/Logger.hpp"

#include "../Graphics/GraphicsContext.hpp"
#include "../Graphics/Sprite.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/Shader.hpp"
using namespace Scramble::Graphics;

namespace Scramble
{
    class Font;
    class Audio;

    class ResourceManager
    {
    typedef std::map<std::string, SharedPtr<Sprite>> SpriteMap;

    typedef std::map<std::string, SharedPtr<Font>> FontMap;
    typedef std::map<std::string, SharedPtr<Audio>> AudioMap;
    typedef std::map<std::string, SharedPtr<Shader>> ShaderMap;
    typedef std::map<std::string, SharedPtr<Texture>> TextureMap;

    private:
        static SpriteMap sprites;

    private:
        static FontMap fonts;
        static AudioMap audio;
        static ShaderMap shaders;
        static TextureMap textures;

    public:
        static void OnStartUp();
        static void OnShutDown();

    public:
        static void CreateSprite(std::string name, WeakPtr<Texture> texture);
        static void CreateSprite(std::string name, WeakPtr<Texture> texture, Rect rect);
        static void CreateSprite(std::string name, WeakPtr<Texture> texture, Vector2* uv);

    public:
        static void CreateTexture(std::string name, U32 width, U32 height, U32 color);

    public:
        static void LoadFont(std::string name, Str filepath);
        static void LoadAudio(std::string name, Str filepath);
        static void LoadShader(std::string name, Str vertexPath, Str fargmentPath);
        static void LoadTexture(std::string name, Str filepath);

    public:
        static WeakPtr<Sprite> GetSprite(std::string name);
    
    public:
        static WeakPtr<Font> GetFont(std::string name);
        static WeakPtr<Audio> GetAudio(std::string name);
        static WeakPtr<Shader> GetShader(std::string name);
        static WeakPtr<Texture> GetTexture(std::string name);
    
    public:
        static void DestroySprite(std::string name);

    public:
        static void DestroyFont(std::string name);
        static void DestroyAudio(std::string name);
        static void DestroyShader(std::string name);
        static void DestroyTexture(std::string name);
    };
}

#endif