#version 440 core

layout(location = 0) in vec3  aPos;
layout(location = 1) in vec4  aColor;
layout(location = 2) in vec2  aTexCoords;
layout(location = 3) in float aTexIndex;

out vec4  fColor;
out vec2  fTexCoords;
out float fTexIndex;

uniform mat4 uViewMatrix;
uniform mat4 uProjMatrix;

vec4 NormalizeColor(vec4 color)
{
    return vec4(color.x / 255.0, color.y / 255.0, color.z / 255.0, color.w / 255.0);
}

void main()
{
    fColor = NormalizeColor(aColor);
    fTexCoords = aTexCoords;
    fTexIndex = aTexIndex;

    vec4 transformedVertex = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    
    transformedVertex = transformedVertex * uViewMatrix;
    transformedVertex = transformedVertex * uProjMatrix;

    gl_Position = transformedVertex;
}