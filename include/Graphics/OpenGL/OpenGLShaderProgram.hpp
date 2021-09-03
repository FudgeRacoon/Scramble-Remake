#ifndef OPENGL_SHADERPROGRAM_HPP
#define OPENGL_SHADERPROGRAM_HPP

#include <string>
#include <sstream>
#include <fstream>

#include "GLEW/glew.h"

#include "Core/Common/Types.hpp"
#include "Core/Logger/Logger.hpp"
#include "Core/Math/Matrix4.hpp"
#include "Core/Math/Vector2.hpp"
#include "Core/Math/Vector4.hpp"

namespace Scramble::Graphics
{
    class OpenGLShaderProgram
    {   
    private:
        U32 shaderProgramId;

    public:
        OpenGLShaderProgram(const char* vertexFilepath, const char* fragmentFilepath);
        ~OpenGLShaderProgram();

    private:
        std::string ParseShader(const char* filepath);
        void CreateShader(const char* filepath, int shaderType);

    public:
        void SetBool(const char* varName, int value) const;
        void SetInt(const char* varName, int value) const;
        void SetFloat(const char* varName, float value) const;
        void SetVec2i(const char* varName, Vector2 v) const;
        void SetVec2f(const char* varName, Vector2 v) const;
        void SetVec4i(const char* varName, Vector4 v) const;
        void SetVec4f(const char* varName, Vector4 v) const;
        void SetMat4(const char* varName, Matrix4 m) const;

    public:
        void Bind() const;
        void UnBind() const;
    };
}

#endif