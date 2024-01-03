#pragma once

#include <nel/nel.hpp>

class Game : public Engine
{
  public:
  Game(int width, int height, const char *title, bool centered) : Engine(width, height, title, centered){};
  // This method is called in the end of the main update
  void onUpdate() override;
  // This method is called in the end of the main setup
  void onSetup() override;
};
