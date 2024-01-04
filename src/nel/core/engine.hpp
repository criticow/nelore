#pragma once

#include <nelpch.hpp>
#include <nel/core/window.hpp>
#include <nel/core/time.hpp>
#include <nel/core/resource_manager.hpp>
#include <nel/core/input.hpp>
#include <nel/ecs/scene.hpp>
#include <nel/ecs/entity.hpp>
#include <nel/core/scene_manager.hpp>
#include <nel/ecs/render_system_3d.hpp>

class Engine
{
  // For public use
  public:
  void run();

  // For Engine class use only
  private:
  void gameLoop();
  void setup();
  void update();
  void render();
  void destroy();

  // For engine and derived classes use
  protected:
  Window window;
  Time time;
  ResourceManager resourceManager;
  Input input;
  SceneManager sceneManager;
  RenderSystem3D renderSystem3D;

  Engine(int width, int height, const char *title, bool centered);

  virtual void onUpdate(){};
  virtual void onSetup(){};
};