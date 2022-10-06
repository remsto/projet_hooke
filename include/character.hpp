#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

class Character : public sf::Drawable {
    private:
        int m_health;
        sf::Vector2f m_position;
        sf::Vector2f m_speed;
        sf::Vector2f m_acceleration;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

    public:
        void update();

        const sf::Vector2f getPosition();
        void setPosition(const sf::Vector2f new_pos);

        const sf::Vector2f getSpeed();
        void setSpeed(const sf::Vector2f new_speed);
        void move(const sf::Vector2f speed);

        const sf::Vector2f getAcceleration();
        void setAcceleration(sf::Vector2f new_acceleration);
        void accelerate(sf::Vector2f acceleration);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Character();
        // ~Character();
};

#endif