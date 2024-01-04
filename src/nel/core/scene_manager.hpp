#pragma once

#include <nelpch.hpp>
#include <nel/ecs/scene.hpp>

class SceneManager
{
  public:
  Scene *activeScene = nullptr;
  Scene &getScene(const std::string &name);
  Scene &createScene(const std::string &name);

  void setActive(const std::string &name);
  bool hasScene(const std::string &name);
  private:
  std::unordered_map<std::string, Scene> scenes;
};