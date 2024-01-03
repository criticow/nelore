#include "game.hpp"

void Game::onUpdate()
{
  if(this->time.justUpdated)
  {
    this->window.setTitle(std::format("{:.2f}ms {:.2f}fps", this->time.ms, this->time.fps));
  }
}

void Game::onSetup()
{
}
