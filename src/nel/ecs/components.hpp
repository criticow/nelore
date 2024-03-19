#pragma once

#include <nelpch.hpp>
#include <nel/resources/texture_2d.hpp>

struct UUID
{
  std::string value;
};

struct Transform
{
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f);
  glm::vec3 scale = glm::vec3(1.0f);
};

struct Projection
{
  enum Type
  {
    PERSPECTIVE,
    ORTHOGRAPHIC
  };

  bool active = false;
  Type type = PERSPECTIVE;
  float fov = 75.0f;
  float near = 0.05f;
  float far = 4000.0f;
};

struct Light
{
  enum Type
  {
    DIRECTIONAL,
    POINT
  };

  Type type = DIRECTIONAL;
  bool castShadow;
  glm::vec3 color = glm::vec3(1.0f);
  glm::vec3 diffuse = color * glm::vec3(1.0f);
  glm::vec3 ambient = color * glm::vec3(0.57f);
  glm::vec3 specular = glm::vec3(1.0f);
};

struct Vertex
{
  glm::vec3 position;
  glm::vec2 texCoords;
  glm::vec3 normal;

  Vertex(void) = default;
  Vertex(const glm::vec3 position, const glm::vec2 texCoords, const glm::vec3 normal) :
    position(position), texCoords(texCoords), normal(normal) {}
};

struct Mesh
{
  std::string name;
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
};

struct Material
{
  Texture2D *diffuseTexture = nullptr;
  glm::vec3 diffuseColor = glm::vec3(0.207f);
  glm::vec3 specularColor = glm::vec3(0.5f);
  float shininess = 250.0f;
};