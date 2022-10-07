#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>
#include "level.hpp"
#include "character.hpp"

class Game {
    private:
        float nu;
        Level level;
        Character character;
        TileMap map;
        sf::RenderWindow window;
        sf::View main_view;

    public:
        // Check if the character is airborne
        bool checkAirborne();
        int runGame();
        void update();
        void stickGround();
        Game();
};
#endif // __GAME_H__