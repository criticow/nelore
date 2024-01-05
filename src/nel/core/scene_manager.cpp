#include "scene_manager.hpp"

Scene &SceneManager::getScene(const std::string &name)
{
  ASSERT(this->hasScene(name), "Scene {} not found", name);
  return this->scenes[name];
}

Scene &SceneManager::createScene(const std::string &name)
{
  this->scenes[name] = Scene(name);
  LOGGER_DEBUG("Created Scene {}", name);
  if(!this->activeScene)
  {
    this->setActive(name);
  }

  return this->scenes[name];
}

void SceneManager::setActive(const std::string &name)
{
  ASSERT(this->hasScene(name), "Scene {} not found", name);
  // The scene is already active
  if(this->activeScene && this->activeScene->name == name)
  {
    return;
  }
  this->activeScene = &this->scenes[name];
  LOGGER_DEBUG("Activated Scene {}", name);
}

bool SceneManager::hasScene(const std::string &name)
{
  return this->scenes.find(name) != this->scenes.end();
}
