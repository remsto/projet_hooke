#include "engine.hpp"
void Engine::updatePhysics(){
    int x_speed = m_character.getSpeed().x;
    int y_speed = m_character.getSpeed().y;
    int x_force = m_character.getForce().x;
    int y_force = m_character.getForce().y;

    // Adds the gravity force, the fluid frottements force, and the character force
    sf::Vector2f new_acceleration = sf::Vector2f(0 - m_nu*x_speed + x_force, \
                                                 1 - m_nu*y_speed + y_force) ;
    m_character.setAcceleration(new_acceleration);
    m_character.updatePhysics();
    m_main_view.setCenter(m_character.getPosition());
}

void Engine::resetLoopConsts(){
    m_character.setForce(sf::Vector2f(0, 0));
    m_character.setAirborne(checkAirborne(m_character));
}

bool Engine::checkAirborne(Entity entity) const{
    // Get varaibles
    sf::IntRect character_rect = entity.getSprite().getTextureRect();
    sf::Vector2f character_pos = entity.getPosition();
    sf::Vector2f low_left(character_pos.x, character_pos.y + character_rect.height);
    sf::Vector2f low_right(character_pos.x + character_rect.width, character_pos.y + character_rect.height);
    int tile_size = m_level.getTileSize();
    std::vector<std::vector<int>> level_content = m_level.getContentArray();

    // Check if the low corners of the character rect are 
    int left_level_value = level_content[(static_cast<int>(low_left.y) + 1) / tile_size][static_cast<int>(low_left.x) / tile_size];
    int right_level_value = level_content[(static_cast<int>(low_right.y) + 1) / tile_size][static_cast<int>(low_right.x) / tile_size];

    return (left_level_value == -1) && (right_level_value == -1);
}

void Engine::handleEvent(sf::Keyboard::Key key){
    if (key == sf::Keyboard::Left){
            m_character.setForce(sf::Vector2f(-1, 0));
    }
    else if (key == sf::Keyboard::Right){
        m_character.setForce(sf::Vector2f(1, 0));
    }

    if (key == sf::Keyboard::Space){
        m_character.setAirborne(true);
        m_character.setSpeed(sf::Vector2f(m_character.getSpeed().x, -20));
    }
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

Engine::Engine() : Engine::Engine(Level(), Character(), sf::View()) {}

Engine::Engine(Level level, Character character, sf::View view){
    m_level = level;
    m_character = character;
    m_main_view = view;
}
