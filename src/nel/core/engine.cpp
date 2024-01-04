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

  // Calling the update function from the derived classes
  this->onUpdate();
}

void Engine::render()
{
  glClear(GL_COLOR_BUFFER_BIT);

  Scene *activeScene = this->sceneManager.activeScene;

  if(activeScene)
  {
    Shader &defaultShader = this->resourceManager.getShader("default");
    defaultShader.use();

    // Temporary
    auto meshView = activeScene->handle.view<Transform, Mesh>();
    for(auto [entity, transform, mesh]: meshView.each())
    {
      if(!this->resourceManager.hasResource<RenderObject>(mesh.name))
      {
        this->resourceManager.loadRenderObject(mesh.name, mesh.vertices, mesh.indices);
      }

      RenderObject &renderObject = this->resourceManager.getRenderObject(mesh.name);
      renderObject.bind();
      renderObject.render(mesh.indices.size());
    }
  }

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
