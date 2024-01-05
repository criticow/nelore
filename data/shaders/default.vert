#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 projectionView;
uniform mat4 model;

out VS_OUT
{
  vec2 texCoords;
  vec3 fragPos;
  vec3 normal;
} vs_out;

void main()
{
  vs_out.texCoords  = texCoords;
  vs_out.fragPos    = vec3(model * vec4(position, 1.0));
  vs_out.normal     = mat3(transpose(inverse(model))) * normal;

  gl_Position       = projectionView * vec4(vs_out.fragPos, 1.0);
}