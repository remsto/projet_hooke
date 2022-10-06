#include <iostream>
#include "game.hpp"
#include "level.hpp"
#include "tile_map.hpp"
#include "character.hpp"

int main()
{
    Game game;
    int exit_code = game.runGame();

    return exit_code;
}