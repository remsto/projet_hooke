#include "entity.hpp"

// Update the Entity position and speed according to his acceleration and speed. 
void Entity::updatePhysics(){
    if (!m_airborne){
        m_speed.y = 0;
        m_acceleration.y = 0;
    }
    m_position += m_speed;
    m_speed += m_acceleration;
    m_sprite.setPosition(m_position);
}

const sf::Vector2f Entity::getPosition(){
    return m_position;
}

void Entity::setPosition(const sf::Vector2f new_pos){
    m_position = new_pos;
}

const sf::Vector2f Entity::getSpeed(){
    return m_speed;
}

void Entity::setSpeed(const sf::Vector2f new_speed){
    m_speed = new_speed;
}

const sf::Vector2f Entity::getAcceleration(){
    return m_acceleration;
}

void Entity::setAcceleration(const sf::Vector2f new_acceleration){
    m_acceleration = new_acceleration;
}

const sf::Vector2f Entity::getForce(){
    return m_force;
}

void Entity::setForce(sf::Vector2f force){
    m_force = force;
}

const sf::Sprite& Entity::getSprite(){
    return m_sprite;
}

void Entity::setAirborne(bool new_airborne){
    m_airborne = new_airborne;
}

bool Entity::getAirborne(){
    return m_airborne;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_sprite);
}