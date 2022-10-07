#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable{
    protected:
        int m_health;

        bool m_airborne;

        // Actually a duplicate of the sprite position. Should it be removed ?
        sf::Vector2f m_position;
        sf::Vector2f m_speed;
        sf::Vector2f m_acceleration;
        sf::Vector2f m_force;

        sf::Texture m_texture;
        sf::Sprite m_sprite;

    public:
        void updatePhysics();

        const sf::Vector2f getPosition();
        void setPosition(const sf::Vector2f new_pos);

        const sf::Vector2f getSpeed();
        void setSpeed(const sf::Vector2f new_speed);

        const sf::Vector2f getAcceleration();
        void setAcceleration(sf::Vector2f new_acceleration);

        const sf::Vector2f getForce();
        void setForce(sf::Vector2f force);

        const sf::Sprite& getSprite();

        void setAirborne(bool new_airborne);

        bool getAirborne();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
#endif // __ENTITY_HPP__