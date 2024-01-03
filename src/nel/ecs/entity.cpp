#include "entity.hpp"
#include <nel/ecs/scene.hpp>

Entity::Entity(Scene *scene)
{
  this->scene = scene;
}