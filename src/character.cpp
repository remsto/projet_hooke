#include "character.hpp"

// Deprecated
void Character::move(const sf::Vector2f speed){
    m_sprite.move(speed);
}

void Character::update(){
    m_position += m_speed;
    m_speed += m_acceleration;
    m_sprite.setPosition(m_position);
}

const sf::Vector2f Character::getPosition(){
    return m_position;
}

void Character::setPosition(const sf::Vector2f new_pos){
    m_position = new_pos;
}

const sf::Vector2f Character::getSpeed(){
    return m_speed;
}

void Character::setSpeed(const sf::Vector2f new_speed){
    m_speed = new_speed;
}

const sf::Vector2f Character::getAcceleration(){
    return m_acceleration;
}

void Character::setAcceleration(const sf::Vector2f new_acceleration){
    m_acceleration = new_acceleration;
}

void Character::accelerate(sf::Vector2f acceleration){
    
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_sprite);
}

Character::Character(){
    // Initialize base values
    m_health = 100;
    m_position = sf::Vector2f(64, 7*32);
    m_speed = sf::Vector2f(0, 0);
    m_acceleration = sf::Vector2f(0, 0);


    m_texture.loadFromFile("assets/carved_pumpkin2.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
}