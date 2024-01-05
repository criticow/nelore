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
  this->sceneManager.createScene("secondary");

  this->sceneManager.setActive("main");

  Scene &main = *this->sceneManager.activeScene;

  Entity entity = main.addEntity();
  entity.addComponent<Transform>();
  entity.addComponent<Mesh>(model.mesh);

  Entity camera = main.addEntity();
  camera.addComponent<Transform>(glm::vec3(0.0f, 10.0f, 15.0f), glm::vec3(0.0f), glm::vec3(1.0f));
  camera.addComponent<Projection>();
  camera.getComponent<Projection>()->active = true;
}
