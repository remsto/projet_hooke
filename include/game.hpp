#ifndef __GAME_H__
#define __GAME_H__

#include "level.hpp"
#include "character.hpp"

class Game {
    private:
        Level level;
        Character character;
    public:
        int runGame();
        void update();
        Game();
};
#endif // __GAME_H__