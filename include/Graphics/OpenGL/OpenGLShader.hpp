#ifndef OPENGL_SHADER_HPP
#define OPENGL_SHADER_HPP

#include <string>
#include <sstream>
#include <fstream>

#include "GLEW/glew.h"

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"

namespace Scramble::Graphics
{
    class OpenGLShader
    {   
    private:
        U32 shaderProgramId;

    public:
        OpenGLShader(const char* vertexPath, const char* fragmentPath);

    public:
        ~OpenGLShader();

    private:
        std::string ParseShader(const char* filepath);
        void CreateShader(const char* filepath, int shaderType);

    public:
        void SetInt(const char* varName, I32 value) const;
        void SetBool(const char* varName, I32 value) const;
        void SetFloat(const char* varName, F32 value) const;
    
    public:
        void SetVec2i(const char* varName, I32 x, I32 y) const;
        void SetVec2f(const char* varName, F32 x, F32 y) const;
    
    public:
        void SetVec4i(const char* varName, I32 x, I32 y, I32 z, I32 w) const;
        void SetVec4f(const char* varName, F32 x, F32 y, F32 z, F32 w) const;
    
    public:
        void SetMat4(const char* varName, const float* data) const;

    public:
        void Bind() const;
        void UnBind() const;
    };
}

#endif