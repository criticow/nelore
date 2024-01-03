#pragma once

#include <nel/nel.hpp>

class Game : public Engine
{
  public:
  Game(int width, int height, const char *title, bool centered) : Engine(width, height, title, centered){};
  void onUpdate() override;
  void onSetup() override;
};
