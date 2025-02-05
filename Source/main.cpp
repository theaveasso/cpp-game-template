#include <cstdlib>

#include "Game.h"
// #include <SDL3/SDL_main.h>

int main(int argc, char *argv[]) {

  Game game;
  if (!game.Init() || !game.LoadMedia()) {
    return EXIT_FAILURE;
  }
  game.Run();

  return EXIT_SUCCESS;
}
