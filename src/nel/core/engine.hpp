#pragma once

#include <nelpch.hpp>
#include <nel/core/window.hpp>
#include <nel/core/time.hpp>

class Engine
{
  public:
  Window window;
  Time time;
  Engine(int width, int height, const char *title, bool centered);
  void run();
  virtual void onUpdate(){};
  virtual void onSetup(){};
  private:
  void gameLoop();
  void setup();
  void update();
};