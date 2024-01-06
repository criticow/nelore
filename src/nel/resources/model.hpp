#pragma once

#include <nelpch.hpp>
#include <nel/ecs/components.hpp>

class Model
{
  public:
  Mesh mesh;
  Material material;
  Model(){};
  Model(const char *path);
};