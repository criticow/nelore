#pragma once

#include <nelpch.hpp>
#include <nel/core/scene_manager.hpp>
#include <nel/core/resource_manager.hpp>
#include <nel/ecs/camera_system.hpp>

class RenderSystem3D
{
  public:
  RenderSystem3D(){};
  RenderSystem3D(SceneManager *sceneManager, ResourceManager *resourceManager, CameraSystem *cameraSystem);
  void render();
  private:
  SceneManager *sceneManager = nullptr;
  ResourceManager *resourceManager = nullptr;
  CameraSystem *cameraSystem = nullptr;
};