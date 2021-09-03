#include "Graphics/OpenGL/OpenGLShaderProgram.hpp"
using namespace Scramble::Graphics;

OpenGLShaderProgram::OpenGLShaderProgram(const char* vertexFilepath, const char* fragmentFilepath)
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

    int result;
    char buffer[512];
    glGetProgramiv(this->shaderProgramId, GL_LINK_STATUS, &result);

    if(result == 0)
    {
        glGetProgramInfoLog(this->shaderProgramId, 512, nullptr, buffer);
        Logger::LogError("Failed to link Shader\n%s", buffer);
        return;
    }
}
OpenGLShaderProgram::~OpenGLShaderProgram()
{
    glDeleteProgram(this->shaderProgramId);
}

std::string OpenGLShaderProgram::ParseShader(const char* filepath)
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
void OpenGLShaderProgram::CreateShader(const char* filepath, int shaderType)
{
    std::string source = ParseShader(filepath);
    if(source.empty())
        return;

    const char* sourceCStr = source.c_str();

    int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    int result;
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

void OpenGLShaderProgram::SetBool(const char* varName, int value) const
{
    int uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform1i(uniformId, value);
}
void OpenGLShaderProgram::SetInt(const char* varName, int value) const
{
    int uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform1i(uniformId, value);
}
void OpenGLShaderProgram::SetFloat(const char* varName, float value) const
{
    int uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform1f(uniformId, value);
}
void OpenGLShaderProgram::SetVec2i(const char* varName, Vector2 v) const
{
    int uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform2i(uniformId, (int)v.x, (int)v.y);
}
void OpenGLShaderProgram::SetVec2f(const char* varName, Vector2 v) const
{
    int uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform2f(uniformId, v.x, v.y);
}
void OpenGLShaderProgram::SetVec4i(const char* varName, Vector4 v) const
{
    int uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform4i(uniformId, (int)v.x, (int)v.y, (int)v.z, (int)v.w);
}
void OpenGLShaderProgram::SetVec4f(const char* varName, Vector4 v) const
{
    int uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniform4f(uniformId, v.x, v.y, v.z, v.w);
}
void OpenGLShaderProgram::SetMat4(const char* varName, Matrix4 m) const
{
    int uniformId = glGetUniformLocation(this->shaderProgramId, varName);
    glUniformMatrix4fv(uniformId, 1, false, m.GetRawData());
}

void OpenGLShaderProgram::Bind() const
{
    glUseProgram(this->shaderProgramId);
}
void OpenGLShaderProgram::UnBind() const
{
    glUseProgram(0);
}