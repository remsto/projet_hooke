#include "character.hpp"


float Character::getBaseForce() const {
    return m_base_force;
}

float Character::getBaseJump() const{
    return m_base_jump;
}


Character::Character(){
    // Initialize base values
    m_max_speed = sf::Vector2f(10, 30);
    m_health = 100;
    m_hitbox = sf::FloatRect(100, 13*32, 32, 32);
    m_speed = sf::Vector2f(0, 0);
    m_base_force = 8;
    m_base_jump = 15;

    // Gravity
    m_acceleration = sf::Vector2f(0, 0);


    m_texture.loadFromFile("assets/carved_pumpkin2.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
}
