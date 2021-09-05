#ifndef SHADER_HPP
#define SHADER_HPP

#include "Core/Common/Types.hpp"
#include "Core/Math/Matrix4.hpp"
#include "Core/Math/Vector2.hpp"
#include "Core/Math/Vector4.hpp"

#include "OpenGL/OpenGLShader.hpp"

namespace Scramble
{
    class ResourceManager;
}

namespace Scramble::Graphics
{
    class Shader
    {
    private:
        OpenGLShader* nativeShader;

    private:
        Shader(const char* vertexPath, const char* fragmentPath);

    private:
        ~Shader();

    public:
        const OpenGLShader* GetNativeShader();

    public:
        void SetInt(const char* varName, I32 value);
        void SetBool(const char* varName, I32 value);
        void SetFloat(const char* varName, F32 value);
    
    public:
        void SetVec2i(const char* varName, Vector2 v);
        void SetVec2f(const char* varName, Vector2 v);
    
    public:
        void SetVec4i(const char* varName, Vector4 v);
        void SetVec4f(const char* varName, Vector4 v);
    
    public:
        void SetMat4(const char* varName, Matrix4 m);
    
    friend ResourceManager;
    };
}

#endif