#version 460 core

out vec4 fragColor;

in VS_OUT
{
  vec2 texCoords;
} fs_in;

struct Material
{
  sampler2D diffuseTexture;
  vec3 diffuseColor;
};

uniform Material material;

void main()
{
  fragColor = vec4(material.diffuseColor, 1.0);
}