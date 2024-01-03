#include "scene.hpp"

#include <nel/ecs/entity.hpp>

Scene::Scene(const std::string &name)
{
  this->name = name;
}

Entity Scene::addEntity()
{
  Entity entity(this);
  entity.handle = this->handle.create();
  entity.addComponent<UUID>(Random::UUID());
  LOGGER_DEBUG("Created Entity {}", entity.getComponent<UUID>()->uuid);

  return entity;
}
