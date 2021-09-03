#include "Graphics/OpenGL/OpenGLLayout.hpp"
using namespace Scramble::Graphics;

size OpenGLLayout::GetSizeOfType(U32 type)
{
    switch(type)
    {
        case GL_FLOAT:         return sizeof(float);
        case GL_UNSIGNED_INT:  return sizeof(U32);
        case GL_UNSIGNED_BYTE: return sizeof(byte); 
    }
}