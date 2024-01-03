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
}

void Game::onSetup()
{
}
