#include "Graphics/OpenGL/OpenGLShader.hpp"
using namespace Scramble::Graphics;

OpenGLShader::OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath)
{
    this->shaderProgramId = glCreateProgram();

    if(this->shaderProgramId == 0)
    {
        Logger::LogError("Failed to create shader program.");
        return;
    }

    CreateShader(vertexFilepath, GL_VERTEX_SHADER);
    CreateShader(fragmentFilepath, GL_FRAGMENT_SHADER);

    glLinkProgram(this->shaderProgramId);
    glValidateProgram(this->shaderProgramId);

    I32 result;
    char buffer[512];
    glGetProgramiv(this->shaderProgramId, GL_LINK_STATUS, &result);

    if(result == 0)
    {
        glGetProgramInfoLog(this->shaderProgramId, 512, nullptr, buffer);
        Logger::LogError("Failed to link Shader\n%s", buffer);
        return;
    }
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(this->shaderProgramId);
}

std::string OpenGLShader::ParseShader(const char* filepath)
{
    std::fstream file(filepath, std::ios::in);

    if(!file)
    {
        Logger::LogError("Failed to open shader file.");
        return std::string();
    }
    
    std::string line;
    std::stringstream ss;

    while(getline(file, line))
        ss << line << '\n';
    
    return ss.str();
}
void OpenGLShader::CreateShader(const char* filepath, I32 shaderType)
{
    std::string source = ParseShader(filepath);
    if(source.empty())
        return;

    const char* sourceCStr = source.c_str();

    I32 shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    I32 result;
    char buffer[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if(result == 0)
    {
        glGetShaderInfoLog(shader, 512, nullptr, buffer);
        switch(shaderType)
        {
            case GL_VERTEX_SHADER: Logger::LogError("Failed to compile Vertex Shader.\n%s", buffer); return;
            case GL_FRAGMENT_SHADER: Logger::LogError("Failed to compile Fragment Shader.\n%s", buffer); return;
        }
    }

    glAttachShader(this->shaderProgramId, shader);
    glDeleteShader(shader);
}

void OpenGLShader::SetInt(const char* varName, I32 value) const
{
    I32 uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform1i(uniformId, value);
}
void OpenGLShader::SetBool(const char* varName, I32 value) const
{
    I32 uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform1i(uniformId, value);
}
void OpenGLShader::SetFloat(const char* varName, F32 value) const
{
    I32 uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform1f(uniformId, value);
}

void OpenGLShader::SetVec2i(const char* varName, I32 x, I32 y) const
{
    I32 uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform2i(uniformId, x, y);
}
void OpenGLShader::SetVec2f(const char* varName, F32 x, F32 y) const
{
    I32 uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform2f(uniformId, x, y);
}

void OpenGLShader::SetVec4i(const char* varName, I32 x, I32 y, I32 z, I32 w) const
{
    I32 uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform4i(uniformId, x, y, z, w);
}
void OpenGLShader::SetVec4f(const char* varName, F32 x, F32 y, F32 z, F32 w) const
{
    I32 uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform4f(uniformId, x, y, z, w);
}

void OpenGLShader::SetMat4(const char* varName, const float* data) const
{
    I32 uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniformMatrix4fv(uniformId, 1, false, data);
}

void OpenGLShader::Bind() const
{
    glUseProgram(this->shaderProgramId);
}
void OpenGLShader::UnBind() const
{
    glUseProgram(0);
}