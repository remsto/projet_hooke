#include <cmath>
#include <iostream>

#include "engine.hpp"
#include "level.hpp"


void Engine::updatePhysics(){

    // Tentative of Newton classic physics. For now has not worked well, so more basic stuff is used

    // int x_speed = m_character.getSpeed().x;
    // int y_speed = m_character.getSpeed().y;
    // int x_force = m_character.getForce().x;
    // int y_force = m_character.getForce().y;

    // // Adds the gravity force, the fluid frottements force, and the character force
    // sf::Vector2f new_acceleration = sf::Vector2f(0 - m_nu*x_speed + x_force, \
    //                                              1 - m_nu*y_speed + y_force) ;

    // Simple gravity
    m_character.setAcceleration(0, 1);

    m_character.updatePhysics();
    // if (!m_character.getAirborne()){
    //     stickGround(m_character);
    // }
    handleCollision(m_character);
    m_character.setSpritePos(m_character.getPosition());
    m_main_view.setCenter(m_character.getPosition());
    std::cout << "WOUAHAOU  x : " << m_character.getPosition().x << " y : " << m_character.getPosition().y << std::endl;

}

void Engine::resetLoopConsts(){
    m_character.setForce(sf::Vector2f(0, 0));
    m_character.setAirborne(checkAirborne(m_character));
}

bool Engine::checkAirborne(const Entity& entity) const{
    // Get varaibles
    sf::IntRect character_rect = entity.getSprite().getTextureRect();
    sf::Vector2f character_pos = entity.getPosition();
    sf::Vector2f low_left(character_pos.x, character_pos.y + character_rect.height);
    sf::Vector2f low_right(character_pos.x + character_rect.width, character_pos.y + character_rect.height);
    int tile_size = m_level.getTileSize();
    std::vector<std::vector<LevelTile>> level_content = m_level.getContentArray();

    // Check if the low corners of the character rect are inside a block
    int left_level_value = level_content[(static_cast<int>(low_left.y) + 1) / tile_size][static_cast<int>(low_left.x) / tile_size];
    int right_level_value = level_content[(static_cast<int>(low_right.y) + 1) / tile_size][static_cast<int>(low_right.x) / tile_size];

    return (left_level_value == -1) && (right_level_value == -1);
}

void Engine::stickGround(Entity& entity) const{
    sf::Vector2f entity_pos = entity.getPosition();
    int new_pos = static_cast<int>(entity_pos.y)/static_cast<int>(m_level.getTileSize());
    entity.setPosition(entity_pos.x, new_pos*m_level.getTileSize());
}

void Engine::handleEvent(sf::Event event){
    // if (key == sf::Keyboard::Left){
    //     m_character.setForce(sf::Vector2f(-m_character.getBaseForce(), 0));
    // }
    // else if (key == sf::Keyboard::Right){
    //     m_character.setForce(sf::Vector2f(m_character.getBaseForce(), 0));
    // }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        m_character.setHorizontalSpeed(-m_character.getBaseForce());
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        m_character.setHorizontalSpeed(m_character.getBaseForce());
    }

    else
        m_character.resetHorizontalSpeed();

    if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Space){
             m_character.setAirborne(true);
            m_character.setVerticalSpeed(-10);
        }
    }
}

bool Engine::checkCollision(const Entity& entity) const{
    // Get varaibles
    sf::FloatRect entity_rect = entity.getHitbox();
    sf::Vector2f entity_pos = entity.getPosition(); // Also top left corner
    
    sf::Vector2f top_right(entity_pos.x + entity_rect.width , entity_pos.y);
    sf::Vector2f low_left(entity_pos.x, entity_pos.y + entity_rect.height );
    sf::Vector2f low_right(entity_pos.x + entity_rect.width , entity_pos.y + entity_rect.height );
    int tile_size = m_level.getTileSize();
    std::vector<std::vector<LevelTile>> level_content = m_level.getContentArray();

    // Check if the low corners of the character rect are inside a block
    LevelTile top_left_value = level_content[static_cast<int>(entity_pos.y) / tile_size][static_cast<int>(entity_pos.x) / tile_size];
    LevelTile top_right_value = level_content[static_cast<int>(low_right.y) / tile_size][static_cast<int>(low_right.x) / tile_size];
    LevelTile low_left_value = level_content[static_cast<int>(low_left.y) / tile_size][static_cast<int>(low_left.x) / tile_size];
    LevelTile low_right_value = level_content[static_cast<int>(low_right.y) / tile_size][static_cast<int>(low_right.x) / tile_size];

    return (top_left_value != -1 || top_right_value != -1 || low_left_value != -1 || low_right_value != -1);
}

void Engine::handleCollision(Entity& entity){
    sf::Vector2f entity_speed = entity.getSpeed();
    float speed_norm = entity_speed.x*entity_speed.x + entity_speed.y*entity_speed.y;
    if (speed_norm != 0){
        sf::Vector2f direction = entity_speed/speed_norm;
        while (checkCollision(entity)){
            entity.addPosition(-direction);
        }
    }

    // for (auto corner : std::vector<sf::Vector2i>( {sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(0, 1)} )){
    //     sf::Vector2f corner_pos(entity_pos.x + corner.x*entity_rect.width, entity_pos.y + corner.y*entity_rect.height);
    //     sf::Vector2f corner_new_pos = corner_pos + entity_speed;
    //     sf::Vector2i tile_pos = getTilePos(corner_pos);
    //     sf::Vector2i new_tile_pos = getTilePos(corner_pos + entity.getSpeed());
        // sf::Vector2i number_of_new_tiles = new_tile_pos - tile_pos;

        // Tentative of more complex collision handling

        // sf::Vector2f corner_real_new_pos;
        // // Go through every pixel in the way and check if there's an obstacle
        // for (sf::Vector2f corner_middle_pos = corner_pos; corner_middle_pos.x <= corner_new_pos.x && corner_middle_pos.y <= corner_new_pos.y; corner_middle_pos += direction){
        //     sf::Vector2i middle_tile_pos = getTilePos(corner_middle_pos);
        //     LevelTile tile_value = level_content[middle_tile_pos.y][middle_tile_pos.x];
        //     if (tile_value != LevelTile::air){
        //         sf::Vector2i diff_tile_pos = middle_tile_pos - getTilePos(corner_middle_pos - direction);
        //         if (diff_tile_pos.x != 0){
                    
        //         }
        //         if (diff_tile_pos.y !=0){

        //         }
        //         else if (diff_tile_pos == sf::Vector2i(0,0))
        //             std::cout << "Error, the diff tile should not be zero" << std::endl;
        //     }
        // }
    // }



    // Change the character position according to these values

    // return (left_level_value == -1) && (right_level_value == -1);
}

sf::Vector2i Engine::getTilePos(const sf::Vector2f pos) const{
    int tile_size = m_level.getTileSize();
    return sf::Vector2i(static_cast<int>(pos.x)/tile_size, static_cast<int>(pos.y)/tile_size);
}

const Character& Engine::getCharacter() const{
    return m_character;
}

const Level& Engine::getLevel() const{
    return m_level;
}

const sf::View& Engine::getMainView() const{
    return m_main_view;
}

Engine::Engine() : Engine::Engine(*(new Level()), *(new Character()), *(new sf::View())) {}

Engine::Engine(Level& level, Character& character, sf::View& view){
    m_nu = 0;
    m_level = level;
    m_character = character;
    m_main_view = view;
}
