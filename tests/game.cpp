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
  // Tests
  this->sceneManager.createScene("main");
  this->sceneManager.createScene("secondary");

  this->sceneManager.setActive("main");

  Scene &main = *this->sceneManager.activeScene;

  Entity entity = main.addEntity();
  entity.addComponent<Transform>();
  std::vector<Vertex> vertices = {
    {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.0f), glm::vec3(0.0f)},
    {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f), glm::vec3(0.0f)},
    {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(0.0f), glm::vec3(0.0f)},
  };
  std::vector<GLuint> indices = {0, 1, 2};
  entity.addComponent<Mesh>("triangle", vertices, indices);

  Scene &secondary = this->sceneManager.getScene("secondary");
  Entity entity2 = secondary.addEntity();
  entity2.addComponent<Transform>();
  std::vector<Vertex> vertices2 = {
    {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f), glm::vec3(0.0f)},
    {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(0.0f), glm::vec3(0.0f)},
    {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f), glm::vec3(0.0f)},
    {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(0.0f), glm::vec3(0.0f)},
  };
  std::vector<GLuint> indices2 = {
    0, 1, 2,
    0, 3, 1
  };

  entity2.addComponent<Mesh>("rectangle", vertices2, indices2);
}
