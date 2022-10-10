#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "game.hpp"
#include "level.hpp"
#include "character.hpp"


int Game::runGame()
{
    // if (!map.load("assets/cobblestone1.png", sf::Vector2u(32, 32), level.getContentArray()))
    //     return -1;

    // Main loop
    while (window.isOpen())
    {
        m_engine.resetLoopConsts();

        // Event management
        sf::Event event;
        while (window.pollEvent(event))
        {
            // if (event.type == sf::Event::KeyPressed){
            //     m_engine.handleEvent(event.key.code);
            // }
            m_engine.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        m_engine.updatePhysics();

        window.setView(m_engine.getMainView());


        window.clear();
        window.draw(m_engine.getLevel().getTileMap());
        window.draw(m_engine.getCharacter());
        window.display();
    }

    return 0;  
}
// void Game::stickGround(){
//     sf::Vector2f character_pos = character.getPosition();
//     character.setPosition(sf::Vector2f(character_pos.x, fmod(character_pos.y, level.getTileSize())));
// }



Game::Game(){

    const unsigned int screen_width = sf::VideoMode::getDesktopMode().width;
    const unsigned int screen_height = sf::VideoMode::getDesktopMode().height;

    m_engine = Engine(*(new Level()), *(new Character()), *(new sf::View(sf::FloatRect(0, 5*32, screen_width/2, screen_height/2))));

    // Window creation
    window.create(sf::VideoMode(screen_width/2, screen_height/2), "Tilemap", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(screen_width/4, screen_height/4));

};