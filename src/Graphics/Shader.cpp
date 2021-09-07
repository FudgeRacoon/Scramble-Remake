#include "Graphics/Shader.hpp"
using namespace Scramble::Graphics;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    this->nativeShader = new OpenGLShader(vertexPath, fragmentPath);
}

Shader::~Shader()
{
    delete this->nativeShader;
}

const OpenGLShader* Shader::GetNativeShader()
{
    return this->nativeShader;
}

void Shader::SetInt(const char* varName, I32 value)
{
    this->nativeShader->SetInt(varName, value);
}
void Shader::SetBool(const char* varName, I32 value)
{
    this->nativeShader->SetBool(varName, value);
}
void Shader::SetFloat(const char* varName, F32 value)
{
    this->nativeShader->SetFloat(varName, value);
}

void Shader::SetVec2i(const char* varName, Vector2 v)
{
    this->nativeShader->SetVec2i(varName, (I32)v.x, (I32)v.y);
}
void Shader::SetVec2f(const char* varName, Vector2 v)
{
    this->nativeShader->SetVec2f(varName, v.x, v.y);
}

void Shader::SetVec4i(const char* varName, Vector4 v)
{
    this->nativeShader->SetVec4i(varName, v.x, v.y, v.z, v.w);
}
void Shader::SetVec4f(const char* varName, Vector4 v)
{
    this->nativeShader->SetVec4f(varName, v.x, v.y, v.z, v.w);
}

void Shader::SetMat4(const char* varName, Matrix4 m)
{
    this->nativeShader->SetMat4(varName, m.GetRawData());
}