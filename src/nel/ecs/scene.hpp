#pragma once

#include <nelpch.hpp>
#include <nel/ecs/components.hpp>
#include <nel/util/random.hpp>

class Entity;

class Scene
{
  public:
  std::string name;
  Scene(){};
  Scene(const std::string &name);

  Entity addEntity();

  private:
  entt::registry handle;
  
  template<typename T, typename... Args>
  T* addComponent(entt::entity entityHandle, Args&&... args)
  {
    return &this->handle.emplace_or_replace<T>(entityHandle, std::forward<Args>(args)...);
  }

  template<typename T>
  T* getComponent(entt::entity entityHandle)
  {
    ASSERT(
      this->hasComponent<T>(entityHandle),
      "Entity {} does not have the component {}",
      entt::to_integral(entityHandle),
      typeid(T).name()
    );
    return &this->handle.get<T>(entityHandle);
  }

  template<typename T>
  bool hasComponent(entt::entity entityHandle)
  {
    return this->handle.any_of<T>(entityHandle);
  }

  friend class Entity;
};