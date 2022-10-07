#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>
#include "level.hpp"
#include "character.hpp"
#include "engine.hpp"

class Game {
    private:
        float nu;
        sf::RenderWindow window;
        Engine m_engine;

    public:
        int runGame();
        void stickGround();
        Game();
};
#endif // __GAME_H__