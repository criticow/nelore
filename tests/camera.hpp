#pragma once

#include <nel/_nel.hpp>

class Camera
{
  public:
  glm::vec3 position;
  Camera(glm::vec3 position, glm::vec3 target);
  void rotate();
  void translate();
};