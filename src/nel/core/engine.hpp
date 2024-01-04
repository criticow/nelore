#pragma once

#include <nelpch.hpp>
#include <nel/core/window.hpp>
#include <nel/core/time.hpp>
#include <nel/core/resource_manager.hpp>
#include <nel/core/input.hpp>
#include <nel/ecs/scene.hpp>
#include <nel/ecs/entity.hpp>
#include <nel/core/scene_manager.hpp>

class Engine
{
  public:
  Window window;
  Time time;
  ResourceManager resourceManager;
  Input input;
  SceneManager sceneManager;
  Engine(int width, int height, const char *title, bool centered);
  void run();
  virtual void onUpdate(){};
  virtual void onSetup(){};
  private:
  void gameLoop();
  void setup();
  void update();
  void render();
  void destroy();
};