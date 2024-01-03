#include "engine.hpp"

Engine::Engine(int width, int height, const char *title, bool centered)
{
  this->window = Window(width, height, title, centered);
  this->window.setUserPointer();
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
  const char *vShaderData = R"(
    #version 460 core
    layout (location = 0) in vec3 position;
    void main()
    {
      gl_Position = vec4(position, 1.0);
    }
  )";

  const char *fShaderData = R"(
    #version 460 core
    out vec4 fragColor;
    void main()
    {
      fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
  )";

  Shader shader(vShaderData, fShaderData);
  this->resourceManager.loadShader("default", shader);

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

  // Calling the update function from the derived classes
  this->onUpdate();
}

void Engine::render()
{
  glClear(GL_COLOR_BUFFER_BIT);
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
