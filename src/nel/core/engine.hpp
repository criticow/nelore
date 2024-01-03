#pragma once

#include <nelpch.hpp>
#include <nel/core/window.hpp>

class Engine
{
  public:
  Window window;
  Engine(int width, int height, const char *title, bool centered);
  void run();
  void setup();
  void update();
  private:
  void gameLoop();
};