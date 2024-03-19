#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out VS_OUT
{
  vec2 texCoords;
} vs_out;

uniform mat4 projectionView;
uniform mat4 model;

void main()
{
  vs_out.texCoords = texCoords;
  gl_Position = projectionView * model * vec4(position, 1.0);
}