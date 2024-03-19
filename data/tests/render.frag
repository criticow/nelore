#version 460 core

in VS_OUT
{
  vec2 texCoords;
} fs_in;

struct Material
{
  vec3 diffuseColor;
}

out vec4 fragColor;

uniform Material material;
uniform vec3 lightColor;

void main()
{
  fragColor = vec4(lightColor * material.diffuseColor, 1.0);
}