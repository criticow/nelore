#pragma once

#include <nelpch.hpp>
#include <nel/core/window.hpp>
#include <nel/core/scene_manager.hpp>

class CameraSystem
{
  public:
  Transform *transform = nullptr;
  Projection *projection = nullptr;
  
  glm::mat4 viewMatrix = glm::mat4(1.0f);
  glm::mat4 projectionMatrix = glm::mat4(1.0f);
  glm::vec3 target = glm::vec3(0.0f);

  CameraSystem(){};
  CameraSystem(Window *window, SceneManager *sceneManager);
  void update();
  private:
  Window *window = nullptr;
  SceneManager *sceneManager = nullptr;
};