#include "character.hpp"


float Character::getBaseForce() const {
    return m_base_force;
}

float Character::getBaseJump() const{
    return m_base_jump;
}

bool Character::isRunning() const{
    return m_is_running;
}

void Character::setRunning(const bool is_running){
    m_is_running = is_running;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_hook);
    target.draw(m_sprite);
}


Character::Character(){
    // Initialize base values
    m_max_speed = sf::Vector2f(10, 30);
    m_health = 100;
    m_hitbox = sf::FloatRect(100, 13*32, 16, 16);
    m_speed = sf::Vector2f(0, 0);
    m_base_force = 1;
    m_base_jump = 15;
    m_hook = Hook(sf::Vector2f(100, 13*32));

    // Gravity
    m_acceleration = sf::Vector2f(0, 0);


    m_texture.loadFromFile("assets/carved_pumpkin2.png");
    m_sprite.setTexture(m_texture);
    m_sprite.scale(0.5, 0.5);
    m_sprite.setPosition(m_position);
}
