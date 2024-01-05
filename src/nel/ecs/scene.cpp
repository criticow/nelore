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
  entity.addComponent<Transform>();

  LOGGER_DEBUG("Created Entity {}", entity.getComponent<UUID>()->value);

  return entity;
}
