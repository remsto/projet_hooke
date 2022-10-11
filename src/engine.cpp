#include <cmath>
#include <iostream>

#include "engine.hpp"
#include "level.hpp"
#include "direction.hpp"


void Engine::updatePhysics(){

    // TODO : Bug when jumping while sticking to a wall : when the upper corner is reached while maintaining the direction toward the wall, 
    // the character cannot move even if he should be able to

    // Simple gravity
    m_character.setVerticalAcceleration(1);

    handleStickCollision(m_character);
    // std::cout << "Acc" << m_character.getAcceleration().x << " " << m_character.getAcceleration().y << std::endl;
    // std::cout << "Speed" << m_character.getSpeed().x << " " << m_character.getSpeed().y << std::endl;

    m_character.updatePhysics();
    handleCollision(m_character);
    m_character.setSpritePos(m_character.getPosition());
    m_main_view.setCenter(m_character.getPosition());

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        m_character.setHorizontalAcceleration(-m_character.getBaseForce());
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        m_character.setHorizontalAcceleration(m_character.getBaseForce());
    }

    else{
        m_character.resetHorizontalSpeed();
        m_character.resetHorizontalAcceleration();
    }

    if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Space){
             m_character.setAirborne(true);
            m_character.setVerticalSpeed(-m_character.getBaseJump());
        }
    }
}

void Engine::handleStickCollision(Entity& entity){
    sf::Vector2f entity_speed = entity.getSpeed();
    sf::Vector2f entity_acceleration = entity.getAcceleration();
    for (auto direction : {sf::Vector2f(-1, 0), sf::Vector2f(0, -1), sf::Vector2f(1, 0), sf::Vector2f(0, 1)}){

        // Check that the entity is moving in the direction
        if (((direction.x * entity_speed.x) > 0) || ((direction.y * entity_speed.y) > 0)){

            // Move one pixel and check the collision
            entity.addPosition(direction);

            // Check the collision only in the interesting direction
            if (checkCollision(entity, ((direction.x < 0) * Direction::Left) | ((direction.y < 0) * Direction::Top) \
                                        | ((direction.x > 0) * Direction::Right) | ((direction.y > 0) * Direction::Bottom))){

                // Sets the speed to 0 only in the interesting direction
                entity.setSpeed(entity_speed.x*(!(entity_speed.x * direction.x > 0)), entity_speed.y*(!(entity_speed.y * direction.y > 0)));
                entity.setAcceleration(entity_acceleration.x*(!((entity_acceleration.x * direction.x) > 0)), entity_acceleration.y*(!((entity_acceleration.y * direction.y) > 0)));
                                        }
            entity.addPosition(-direction);
        }
    }
}

bool Engine::checkCollision(const Entity& entity, unsigned int direction = Direction::Left | Direction::Top | Direction::Right | Direction::Bottom) const{
    // Get varaibles
    sf::FloatRect entity_rect = entity.getHitbox();
    sf::Vector2f entity_pos = entity.getPosition(); // Also top left corner
    sf::Vector2f top_right(entity_pos.x + entity_rect.width , entity_pos.y);
    sf::Vector2f low_left(entity_pos.x, entity_pos.y + entity_rect.height );
    sf::Vector2f low_right(entity_pos.x + entity_rect.width , entity_pos.y + entity_rect.height );
    int tile_size = m_level.getTileSize();
    std::vector<std::vector<LevelTile>> level_content = m_level.getContentArray();

    // Check if the low corners of the character rect are inside a block
    LevelTile top_left_value = (direction & (Direction::Left | Direction::Top)) ? \
                                    level_content[static_cast<int>(entity_pos.y) / tile_size][static_cast<int>(entity_pos.x) / tile_size] : LevelTile::Air;
    LevelTile top_right_value = (direction & (Direction::Right | Direction::Top)) ? \
                                    level_content[static_cast<int>(low_right.y) / tile_size][static_cast<int>(low_right.x) / tile_size] : LevelTile::Air;
    LevelTile low_left_value = (direction & (Direction::Bottom | Direction::Left)) ? \
                                    level_content[static_cast<int>(low_left.y) / tile_size][static_cast<int>(low_left.x) / tile_size] : LevelTile::Air;
    LevelTile low_right_value = (direction & (Direction::Bottom | Direction::Right)) ? \
                                    level_content[static_cast<int>(low_right.y) / tile_size][static_cast<int>(low_right.x) / tile_size] : LevelTile::Air;

    return (top_left_value != LevelTile::Air || top_right_value != LevelTile::Air || low_left_value != LevelTile::Air || low_right_value != LevelTile::Air);
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
