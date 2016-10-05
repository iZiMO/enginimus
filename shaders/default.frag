#version 330 core

struct Material {
    sampler2D textureDiffuse1;
    sampler2D textureDiffuse2;
    sampler2D textureSpecular1;
};

in	vec2 TexCoord;

out vec4 color;

uniform Material material;

void main()
{
    color = mix(texture(material.textureDiffuse1, TexCoord), texture(material.textureDiffuse2, TexCoord), 0.5);
}