#include "game.hpp"
#include <nel/nel.hpp>

int main()
{
  Game game(1280, 720, "Game", true);
  game.run();

  return 0;
}