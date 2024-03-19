#include "game.hpp"

Entity cube3;
glm::vec3 target(0.0f);

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

  if(this->input.held(ACTION_LEFT))
  {
    target.x -= 10.0f * this->time.deltaTime;
  }

  if(this->input.held(ACTION_RIGHT))
  {
    target.x += 10.0f * this->time.deltaTime;
  }

  if(this->input.held(ACTION_JUMP))
  {
    target.y += 10.0f * this->time.deltaTime;
  }

  if(this->input.held(ACTION_FALL))
  {
    target.y -= 10.0f * this->time.deltaTime;
  }

  if(this->input.held(ACTION_FORWARD))
  {
    target.z -= 10.0f * this->time.deltaTime;
  }

  if(this->input.held(ACTION_BACKWARD))
  {
    target.z += 10.0f * this->time.deltaTime;
  }

  cube3.getComponent<Transform>()->rotation.y += 60.0f * this->time.deltaTime;

  this->cameraSystem.target = target;
}

void Game::onSetup()
{
  Model &unwrappedCube = this->resourceManager.loadModel("unwrappedCube", "data/models/unwrapped_cube.gltf");

  // Tests
  this->sceneManager.createScene("main");

  Scene &main = *this->sceneManager.activeScene;

  // Directional Light
  Entity dirLight = main.addEntity();
  dirLight.addComponent<Light>();
  dirLight.addComponent<Transform>();
  Transform *lTransform = dirLight.getComponent<Transform>();
  lTransform->rotation = glm::vec3(-50.0f, 30.0f, 0.0f);

  // Camera
  Entity camera = main.addEntity();
  camera.addComponent<Projection>();

  // Floor
  Entity floor = main.addEntity();
  floor.addComponent<Mesh>(unwrappedCube.mesh);
  floor.addComponent<Material>(unwrappedCube.material);
  Transform *fTrans = floor.getComponent<Transform>();
  fTrans->scale = glm::vec3(12.5f, 1.0f, 12.5f);
  fTrans->position.y = -2.0f;

  // Cubes
  Entity cube1 = main.addEntity();
  cube1.addComponent<Mesh>(unwrappedCube.mesh);
  cube1.addComponent<Material>(unwrappedCube.material);
  Transform *c1Trans = cube1.getComponent<Transform>();
  c1Trans->position = glm::vec3(0.0f, 1.5f, 0.0f);
  c1Trans->scale = glm::vec3(0.5f);

  Entity cube2 = main.addEntity();
  cube2.addComponent<Mesh>(unwrappedCube.mesh);
  cube2.addComponent<Material>(unwrappedCube.material);
  Transform *c2Trans = cube2.getComponent<Transform>();
  c2Trans->position = glm::vec3(2.0f, 0.0f, 1.0f);
  c2Trans->scale = glm::vec3(0.5f);

  cube3 = main.addEntity();
  cube3.addComponent<Mesh>(unwrappedCube.mesh);
  cube3.addComponent<Material>(unwrappedCube.material);
  Transform *c3Trans = cube3.getComponent<Transform>();
  c3Trans->position = glm::vec3(-1.0f, 0.0f, 2.0f);
  // c3Trans->rotation = glm::vec3(60.0f, 0.0f, 60.0f);
  c3Trans->scale = glm::vec3(0.25f);

  Transform *cameraTransform = camera.getComponent<Transform>();
  // cameraTransform->position = glm::vec3(-3.0f, 4.0f, 10.0f);
  cameraTransform->position = glm::vec3(0.0f, 1.0f, 10.0f);
  Projection *projection = camera.getComponent<Projection>();
  projection->active = true;
  projection->near = 0.3f;
  projection->far = 1000.0f;
  projection->fov = 60.0f;
}