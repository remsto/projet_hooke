#ifndef __HOOK_HPP__
#define __HOOK_HPP__

#include <SFML/Graphics.hpp>

class Hook : public sf::Drawable{
    private:
        float m_speed;
        sf::Vector2f m_origin;
        float m_angle;
        float m_length;
        sf::RectangleShape m_line;
    public:
        void setOrigin(const sf::Vector2f origin);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Hook();
        Hook(sf::Vector2f origin);
};

#endif // __HOOK_HPP__