#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "game.hpp"
#include "level.hpp"
#include "character.hpp"


int Game::runGame()
{
    if (!map.load("assets/cobblestone1.png", sf::Vector2u(32, 32), level.getContentArray()))
        return -1;

    // Main loop
    while (window.isOpen())
    {

        character.setCharacterForce(sf::Vector2f(0, 0));
        character.setAirborne(checkAirborne());

        // Event management
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Left){
                    character.setCharacterForce(sf::Vector2f(-1, 0));
                }
                else if (event.key.code == sf::Keyboard::Right){
                    character.setCharacterForce(sf::Vector2f(1, 0));
                }

                if (event.key.code == sf::Keyboard::Space){
                    character.setAirborne(true);
                    character.setSpeed(sf::Vector2f(character.getSpeed().x, -20));
                }
                // else if (event.key.code == sf::Keyboard::Up)
                //     main_view.move(sf::Vector2f(0, -10));
                // else if (event.key.code == sf::Keyboard::Down)
                //     main_view.move(sf::Vector2f(0, 10));
            }
            else if (event.type == sf::Event::Closed)
                window.close();
        }

        // std::cout << checkAirborne() << std::endl;
        
        update();

        main_view.setCenter(character.getPosition());

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
    sf::Vector2f new_acceleration = sf::Vector2f(0 - nu*x_speed + x_force, \
                                                 1 - nu*y_speed + y_force) ;
    character.setAcceleration(new_acceleration);
    character.update();
}

void Game::stickGround(){
    sf::Vector2f character_pos = character.getPosition();
    character.setPosition(sf::Vector2f(character_pos.x, fmod(character_pos.y, level.getTileSize())));
}

bool Game::checkAirborne(){
    // Get varaibles
    sf::IntRect character_rect = character.getSprite().getTextureRect();
    sf::Vector2f character_pos = character.getPosition();
    sf::Vector2f low_left(character_pos.x, character_pos.y + character_rect.height);
    sf::Vector2f low_right(character_pos.x + character_rect.width, character_pos.y + character_rect.height);
    int tile_size = level.getTileSize();
    std::vector<std::vector<int>> level_content = level.getContentArray();

    // Check if the low corners of the character rect are 
    int left_level_value = level_content[(static_cast<int>(low_left.y) + 1) / tile_size][static_cast<int>(low_left.x) / tile_size];
    int right_level_value = level_content[(static_cast<int>(low_right.y) + 1) / tile_size][static_cast<int>(low_right.x) / tile_size];

    // std::cout << "x : " << character_pos.x << " , y : " << character_pos.y << std::endl;
    // std::cout << "left_tile_y : " << (static_cast<int>(low_left.y) + 1) / tile_size << " , left_tile_x : " << (static_cast<int>(low_left.x) + 1) / tile_size << std::endl;
    // std::cout << "right_tile_y : " << (static_cast<int>(low_right.y) + 1) / tile_size << " , right_tile_x : " << (static_cast<int>(low_right.x) + 1) / tile_size << std::endl;


    return (left_level_value == -1) && (right_level_value == -1);
}

Game::Game(){
    // Fluid frottements constant
    nu = 0.01;

    const unsigned int screen_width = sf::VideoMode::getDesktopMode().width;
    const unsigned int screen_height = sf::VideoMode::getDesktopMode().height;

    // Window creation
    window.create(sf::VideoMode(screen_width/2, screen_height/2), "Tilemap", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(screen_width/4, screen_height/4));

    // Main view creation
    main_view = sf::View(sf::FloatRect(0, 5*32, screen_width/2, screen_height/2));
    window.setView(main_view);

    // Tile map creation
    TileMap map;
};