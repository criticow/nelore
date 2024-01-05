#include "engine.hpp"

#include <nel/ecs/render_system_3d.hpp>

Engine::Engine(int width, int height, const char *title, bool centered)
{
  this->window = Window(width, height, title, centered);
  this->window.setUserPointer();
  this->renderSystem3D = RenderSystem3D(&this->sceneManager, &this->resourceManager, &this->cameraSystem);
  this->cameraSystem = CameraSystem(&this->window, &this->sceneManager);
}

void Engine::run()
{
  std::thread gameThread(&Engine::gameLoop, this);

  while(this->window.isOpen())
  {
    this->window.pollEvents();
  }

  gameThread.join();
  this->destroy();
}

void Engine::setup()
{
  this->window.loadOpenGL();
  this->resourceManager.loadShader("default", "data/shaders/default.vert", "data/shaders/default.frag");

  // Calling the setup from the derived classes
  this->onSetup();
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
  this->input.update(this->window);

  // Systems update cycle starts
  this->cameraSystem.update();
  // Systems update cycle ends

  // Calling the update function from the derived classes
  this->onUpdate();
}

void Engine::render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Systems render cycle starts
  this->renderSystem3D.render();
  // Systems render cycle ends

  this->window.swapBuffers();
}

void Engine::destroy()
{
  this->resourceManager.destroy();
  this->window.destroy();
}

void Engine::gameLoop()
{
  this->setup();
  while(this->window.isOpen())
  {
    this->update();
    this->render();
  }
}
