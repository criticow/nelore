#include "engine.hpp"

#include <nel/ecs/render_system_3d.hpp>

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
  if (quadVAO == 0)
  {
    float quadVertices[] = {
        // positions        // texture Coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
          1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
          1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  }
  glBindVertexArray(quadVAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);
}

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
    this->window.waitEvents();
  }

  gameThread.join();
  this->destroy();
}

void Engine::setup()
{
  this->window.loadOpenGL();
  glClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);
  this->resourceManager.loadShader("default", "data/shaders/default.vert", "data/shaders/default.frag");
  this->resourceManager.loadShader("depth", "data/shaders/depth.vert", "data/shaders/depth.frag");
  this->resourceManager.loadShader("depthDebug", "data/shaders/depthDebug.vert", "data/shaders/depthDebug.frag");

  Texture2D &depthMap = this->resourceManager.loadTexture2D("depthMap", Texture2D(1024, 1024));
  this->resourceManager.loadFramebuffer("depthMap", depthMap);

  // Calling the setup from the derived classes
  this->onSetup();
}

void Engine::update()
{
  // Update opengl viewport if the framebuffer is updated
  this->window.framebufferMutex.lock();
  if(this->window.isFramebufferUpdated)
  {
    this->window.isFramebufferUpdated = false;
    glViewport(0, 0, this->window.width, this->window.height);
  }
  this->window.framebufferMutex.unlock();

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
    // Check if there is a directional light and if it is casting shadows
    this->render();
  }
}
