#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "level.hpp"
#include "character.hpp"


int Game::runGame()
{

    
   
    if (!map.load("assets/cobblestone1.png", sf::Vector2u(32, 32), level.getContentArray()))
        return -1;

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            character.setCharacterForce(sf::Vector2f(0, 0));
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Left){
                    character.setCharacterForce(sf::Vector2f(-1, 0));
                }
                else if (event.key.code == sf::Keyboard::Right){
                    character.setCharacterForce(sf::Vector2f(1, 0));
                }
                // else if (event.key.code == sf::Keyboard::Up)
                //     main_view.move(sf::Vector2f(0, -10));
                // else if (event.key.code == sf::Keyboard::Down)
                //     main_view.move(sf::Vector2f(0, 10));
            }
            else if (event.type == sf::Event::Closed)
                window.close();
            // else
            //     character.setSpeed(sf::Vector2f(0, 0));
        }
        
        update();
        // on dessine le niveau

        // Pour une raison inconnue, le fait de setView ici étire la fenetre
        window.setView(main_view);


        window.clear();
        window.draw(map);
        window.draw(character);
        window.display();
    }

    return 0;  
}

void Game::update(){
    int x_speed = character.getSpeed().x;
    int y_speed = character.getSpeed().y;
    int x_force = character.getCharacterForce().x;
    int y_force = character.getCharacterForce().y;

    // Adds the gravity force, the fluid frottements force, and the character force
    sf::Vector2f new_acceleration = sf::Vector2f(0 - nu*(x_speed*x_speed)*((x_speed > 0) - (x_speed < 0)) + x_force, \
                                                 0 - nu*(y_speed*y_speed)*((y_speed > 0) - (y_speed < 0)) + y_force) ;
    character.setAcceleration(new_acceleration);
    character.update();
    main_view.setCenter(character.getPosition());
}

Game::Game(){
    nu = 0.1;
    const unsigned int screen_width = sf::VideoMode::getDesktopMode().width;
    const unsigned int screen_height = sf::VideoMode::getDesktopMode().height;
    // level.printContent();


    // on crée la fenêtre
    window.create(sf::VideoMode(screen_width/2, screen_height/2), "Tilemap", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(screen_width/4, screen_height/4));



    main_view = sf::View(sf::FloatRect(0, 5*32, screen_width/2, screen_height/2));
    window.setView(main_view);
    

    // on crée la tilemap avec le niveau précédemment défini
    TileMap map;
};