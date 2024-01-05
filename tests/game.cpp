#include "game.hpp"

void Game::onUpdate()
{
  if(this->time.justUpdated)
  {
   this->window.setTitle(std::format("{:.2f}ms {:.2f}fps", this->time.ms, this->time.fps));
  }

  if(this->input.pressed(ACTION_CANCEL))
  {
    this->window.close();
  }

  // Tests
  if(this->input.pressed(KEY_F1))
  {
    this->sceneManager.setActive("main");
  }

  if(this->input.pressed(KEY_F2))
  {
    this->sceneManager.setActive("secondary");
  }
}

void Game::onSetup()
{
  Model &model = this->resourceManager.loadModel("cube", "data/models/cube.gltf");

  // Tests
  this->sceneManager.createScene("main");

  Scene &main = *this->sceneManager.activeScene;

  Entity cube = main.addEntity();
  cube.addComponent<Mesh>(model.mesh);
  cube.addComponent<Material>();
  cube.getComponent<Material>()->diffuseColor = glm::vec3(1.0f);
  Transform *cubeTransform = cube.getComponent<Transform>();
  cubeTransform->scale = glm::vec3(15.0f, 1.0f, 15.0f);

  Entity cube2 = main.addEntity();
  cube2.addComponent<Mesh>(model.mesh);
  cube2.addComponent<Material>();
  Transform *cube2Transform = cube2.getComponent<Transform>();
  cube2Transform->position = glm::vec3(16.0f, 1.5f, 0.0f);

  Entity dirLight = main.addEntity();
  dirLight.addComponent<Light>();
  dirLight.addComponent<Transform>();

  Entity camera = main.addEntity();
  camera.addComponent<Projection>();

  Transform *cameraTransform = camera.getComponent<Transform>();
  cameraTransform->position = glm::vec3(0.0f, 10.0f, 15.0f);
  camera.getComponent<Projection>()->active = true;
}
