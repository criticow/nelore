#pragma once

#include <nelpch.hpp>
#include <nel/ecs/scene.hpp>

class Entity
{
  public:
  Entity(){};
  Entity(Scene *scene);

  template<typename T, typename... Args>
  T *addComponent(Args&&... args)
  {
    ASSERT(this->scene, "Scene not found/initialized");
    return this->scene->addComponent<T>(this->handle, std::forward<Args>(args)...);
  }

  template<typename T>
  T *getComponent()
  {
    return this->scene->getComponent<T>(this->handle);
  }

  template<typename T>
  bool hasComponent()
  {
    return this->scene->hasComponent<T>(this->handle);
  }

  private:
  entt::entity handle;
  Scene *scene = nullptr;

  friend class Scene;
};