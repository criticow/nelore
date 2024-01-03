#include "engine.hpp"

Engine::Engine(int width, int height, const char *title, bool centered)
{
  this->window = Window(width, height, title, centered);
}

void Engine::run()
{
  std::thread gameThread(&Engine::gameLoop, this);

  while(this->window.isOpen())
  {
    this->window.pollEvents();
  }

  gameThread.join();
  this->window.destroy();
}

void Engine::setup()
{
  this->window.setUserPointer();
}

void Engine::update()
{
  // Update opengl viewport if the framebuffer is updated
  this->window.fbMutex.lock();
  if(this->window.isFramebufferUpdated)
  {
    this->window.isFramebufferUpdated = false;
    glViewport(0, 0, this->window.width, this->window.height);
  }
  this->window.fbMutex.unlock();

  this->time.update();

  if(this->time.justUpdated)
  {
    this->window.setTitle(std::format("{:.2f}ms {:.2f}fps", this->time.ms, this->time.fps));
  }
}

void Engine::gameLoop()
{
  this->window.loadOpenGL();
  this->setup();
  while(this->window.isOpen())
  {
    this->update();
    glClear(GL_COLOR_BUFFER_BIT);
    this->window.swapBuffers();
  }
}
