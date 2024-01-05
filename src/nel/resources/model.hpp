#pragma once

#include <nelpch.hpp>
#include <nel/ecs/components.hpp>

class Model
{
  public:
  Mesh mesh;
  Model(){};
  Model(const char *path);
};