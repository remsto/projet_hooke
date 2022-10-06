#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "level.hpp"
#include "character.hpp"


int Game::runGame()
{
    const unsigned int screen_width = sf::VideoMode::getDesktopMode().width;
    const unsigned int screen_height = sf::VideoMode::getDesktopMode().height;
    // level.printContent();

     // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(screen_width/2, screen_height/2), "Tilemap", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(screen_width/4, screen_height/4));

    sf::View main_view = sf::View(sf::FloatRect(0, 5*32, screen_width/2, screen_height/2));
    window.setView(main_view);

    // on crée la tilemap avec le niveau précédemment défini
    TileMap map;
    if (!map.load("assets/cobblestone1.png", sf::Vector2u(32, 32), level.getContentArray()))
        return -1;

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Left){
                    main_view.move(sf::Vector2f(-10, 0));
                    character.move(sf::Vector2f(-10, 0));
                }
                else if (event.key.code == sf::Keyboard::Right){
                    main_view.move(sf::Vector2f(10, 0));
                    character.move(sf::Vector2f(10, 0));
                }
                // else if (event.key.code == sf::Keyboard::Up)
                //     main_view.move(sf::Vector2f(0, -10));
                // else if (event.key.code == sf::Keyboard::Down)
                //     main_view.move(sf::Vector2f(0, 10));
                window.setView(main_view);
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // on dessine le niveau
        window.clear();
        window.draw(map);
        window.draw(character);
        window.display();
    }

    return 0;  
}

void Game::update(){
    
}

Game::Game(){};