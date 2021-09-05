#version 440 core

in vec4 fColor;
in vec2 fTexCoords;
in float fTexIndex;

out vec4 color;

uniform sampler2D textures[32];

void main()
{
    vec4 texel = texture(textures[int(fTexIndex)], fTexCoords) * fColor;

    if(texel.w < 0.1)
        discard;

    color = texel;
}