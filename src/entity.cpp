#include <cstdlib>
#include <iostream>
#include "entity.hpp"

void Entity::updateSpeed(){
    m_speed += m_acceleration;

    if (m_speed.x > m_max_speed.x)
        m_speed.x = m_max_speed.x;
    else if (-m_speed.x > m_max_speed.x)
        m_speed.x = -m_max_speed.x;
    if (m_speed.y > m_max_speed.y)
        m_speed.y = m_max_speed.y;
    else if (-m_speed.y > m_max_speed.y)
        m_speed.y = -m_max_speed.y;
}

// Update the Entity position and speed according to its acceleration and speed. 
void Entity::updatePosition(){
    addPosition(m_speed);

}

sf::FloatRect Entity::getHitbox() const{
    return m_hitbox;
}

sf::Vector2f Entity::getPosition() const{
    return sf::Vector2f(m_hitbox.left, m_hitbox.top);
}

void Entity::setPosition(const sf::Vector2f new_pos){
    m_hitbox.left = new_pos.x;
    m_hitbox.top = new_pos.y;
}

void Entity::setPosition(float x, float y){
    m_hitbox.left = x;
    m_hitbox.top = y;
}

void Entity::addPosition(const sf::Vector2f pos){
    m_hitbox.left += pos.x;
    m_hitbox.top += pos.y;
}

void Entity::addPosition(float x, float y){
    m_hitbox.left += x;
    m_hitbox.top += y;
}

sf::Vector2f Entity::getSpeed() const{
    return m_speed;
}

void Entity::setSpeed(const sf::Vector2f new_speed){
    m_speed = new_speed;
}

void Entity::setSpeed(float x, float y){
    setSpeed(sf::Vector2f(x, y));
}

void Entity::setHorizontalSpeed(float new_horizontal_speed){
    setSpeed(new_horizontal_speed, getSpeed().y);
}

void Entity::resetHorizontalSpeed(){
    setSpeed(0, getSpeed().y);
}

void Entity::setVerticalSpeed(float new_vertical_speed){
    m_speed = sf::Vector2f(getSpeed().x, new_vertical_speed);
}

void Entity::resetVerticalSpeed(){
    setSpeed(getSpeed().x, 0);
}

sf::Vector2f Entity::getAcceleration() const{
    return m_acceleration;
}

void Entity::setAcceleration(const sf::Vector2f new_acceleration){
    m_acceleration = new_acceleration;
}

void Entity::setAcceleration(float x, float y){
    setAcceleration(sf::Vector2f(x, y));
}

void Entity::setHorizontalAcceleration(float new_horizontal_acceleration){
    m_acceleration = sf::Vector2f(new_horizontal_acceleration, getAcceleration().y);
}

void Entity::resetHorizontalAcceleration(){
    m_acceleration = sf::Vector2f(0, getAcceleration().y);
}

void Entity::setVerticalAcceleration(float new_vertical_acceleration){
    m_acceleration = sf::Vector2f(getAcceleration().x, new_vertical_acceleration);
}

void Entity::resetVerticalAcceleration(){
    m_acceleration = sf::Vector2f(getAcceleration().x, 0);
}

sf::Vector2f Entity::getForce() const{
    return m_force;
}

void Entity::setForce(const sf::Vector2f force){
    m_force = force;
}

void Entity::setForce(float x, float y){
    setForce(sf::Vector2f(x, y));
}

void Entity::setHorizontalForce(float new_horizontal_force){
    m_force = sf::Vector2f(new_horizontal_force, getForce().y);
}

void Entity::resetHorizontalForce(){
    m_force = sf::Vector2f(0, getForce().y);
}

void Entity::setVerticalForce(float new_vertical_force){
    m_force = sf::Vector2f(getForce().x, new_vertical_force);
}

void Entity::resetVerticalForce(){
    m_force = sf::Vector2f(getForce().x, 0);
}

const sf::Sprite& Entity::getSprite() const{
    return m_sprite;
}

void Entity::setSpritePos(sf::Vector2f pos){
    m_sprite.setPosition(pos);
}

void Entity::setAirborne(bool new_airborne){
    m_airborne = new_airborne;
}

bool Entity::getAirborne() const{
    return m_airborne;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_sprite);
}

