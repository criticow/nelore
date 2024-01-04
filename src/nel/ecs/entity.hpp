#pragma once

#include <nelpch.hpp>
#include <nel/ecs/scene.hpp>

class Entity
{
  public:
  entt::entity handle;

  Entity(){};
  Entity(Scene *scene);

  template<typename T, typename... Args>
  T* addComponent(Args&&... args)
  {
    return &this->scene->handle.emplace_or_replace<T>(this->handle, std::forward<Args>(args)...);
  }

  template<typename T>
  T* getComponent()
  {
    std::string uuid = this->scene->handle.get<UUID>(this->handle).value;
    // Makes sure the entity has the component
    ASSERT(this->hasComponent<T>(), "Entity {} does not have the component {}", uuid, typeid(T).name());
    return &this->scene->handle.get<T>(this->handle);
  }

  template<typename T>
  bool hasComponent()
  {
    return this->scene->handle.any_of<T>(this->handle);
  }

  private:
  Scene *scene = nullptr;

  friend class Scene;
};