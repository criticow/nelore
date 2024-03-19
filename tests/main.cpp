#include <nel/_nel.hpp>

Window window(1280, 720, "Game", true);
ResourceManager resManager;
Time gameTime;
void gameLoop();

int main()
{
  window.setUserPointer();
  std::thread gameThread(gameLoop);

  while(window.isOpen())
  {
    window.waitEvents();
  }

  gameThread.join();
  window.destroy();

  return 0;
}

void gameLoop()
{
  window.loadOpenGL();
  glClearColor(0.207f, 0.207f, 0.207f, 1.0f);
  Shader &defaultShader = resManager.loadShader("default", "data/shaders/render.vert", "data/shaders/render.frag");
  Model &protoCube = resManager.loadModel("protocube", "data/models/protocube.gltf");
  Material orangeMat{ .diffuseColor = glm::vec3(1.0f, 0.5f, 0.31f) };
  Material whiteMat{ .diffuseColor = glm::vec3(1.0f) };

  RenderObject protoCubeRO(protoCube.mesh.vertices, protoCube.mesh.indices);

  glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(window.width) / static_cast<float>(window.height), 0.1f, 100.0f);
  glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 model(1.0f);
  glm::vec3 rotation(0.0f);

  while(window.isOpen())
  {
    gameTime.update();
    window.updateViewport();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    defaultShader.use();

    protoCube.material.diffuseTexture->bind();
    // defaultShader.setInt("material.diffuseTexture", 0);
    defaultShader.setFloat("material.diffuseColor", orangeMat.diffuseColor);
    defaultShader.setMatrix("projectionView", projMatrix * viewMatrix);
    defaultShader.setMatrix("model", model);

    protoCubeRO.bind();
    protoCubeRO.render(protoCube.mesh.indices.size());

    window.swapBuffers();
  }
}
