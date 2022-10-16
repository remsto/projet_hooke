#include "hook.hpp"

void Hook::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_line);
}

Hook::Hook() : Hook(sf::Vector2f(0, 0)){};

Hook::Hook(sf::Vector2f origin){
    m_speed = 1.f;
    m_angle = 0.f;
    m_length= 0.f;
    m_line = sf::RectangleShape(sf::Vector2f(6.f, 3.f));
    m_origin = origin;
    m_line.setOrigin(0, m_line.getSize().y / 2);
    m_line.setPosition(origin);
}
