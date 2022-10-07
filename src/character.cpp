#include "character.hpp"



Character::Character(){
    // Initialize base values
    m_health = 100;
    m_position = sf::Vector2f(64, 14*32);
    m_speed = sf::Vector2f(0, 0);

    // Gravity
    m_acceleration = sf::Vector2f(0, 0);


    m_texture.loadFromFile("assets/carved_pumpkin2.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
}