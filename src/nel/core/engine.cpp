#include "engine.hpp"

Engine::Engine(int width, int height, const char *title, bool centered)
{
  this->window = Window(width, height, title, centered);
}

void Engine::run()
{
  this->window.loadOpenGL();
  while(this->window.isOpen())
  {
    this->window.pollEvents();
    this->window.swapBuffers();
  }
  this->window.destroy();
}

void Engine::setup()
{
}
