#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "game.hpp"
#include "level.hpp"
#include "character.hpp"


int Game::runGame()
{
    // Main loop
    while (window.isOpen())
    {
        m_engine.resetLoopConsts();

        // Event management
        sf::Event event;
        while (window.pollEvent(event))
        {
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



Game::Game(){

    const unsigned int screen_width = sf::VideoMode::getDesktopMode().width;
    const unsigned int screen_height = sf::VideoMode::getDesktopMode().height;

    m_engine = Engine(*(new Level()), *(new Character()), *(new sf::View(sf::FloatRect(0, 5*32, screen_width/2, screen_height/2))));

    // Window creation
    window.create(sf::VideoMode(screen_width/2, screen_height/2), "Tilemap", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(screen_width/4, screen_height/4));

};