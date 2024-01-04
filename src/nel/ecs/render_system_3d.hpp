#pragma once

#include <nelpch.hpp>
#include <nel/core/scene_manager.hpp>
#include <nel/core/resource_manager.hpp>

class RenderSystem3D
{
  public:
  RenderSystem3D(){};
  RenderSystem3D(SceneManager *sceneManager, ResourceManager *resourceManager);
  void render();
  private:
  SceneManager *sceneManager = nullptr;
  ResourceManager *resourceManager = nullptr;
};