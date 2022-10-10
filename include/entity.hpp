#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/Graphics.hpp>

// Physic entity. Maybe the physics methods should be refactored
class Entity : public sf::Drawable{
    protected:
        int m_health;

        bool m_airborne;

        sf::FloatRect m_hitbox;

        // Actually a duplicate of the sprite position. Should it be removed ?
        sf::Vector2f m_position;
        sf::Vector2f m_speed;
        sf::Vector2f m_max_speed;
        sf::Vector2f m_acceleration;
        sf::Vector2f m_force;

        sf::Texture m_texture;
        sf::Sprite m_sprite;

    public:
        void updatePhysics();

        sf::FloatRect getHitbox() const;

        sf::Vector2f getPosition() const;
        void setPosition(const sf::Vector2f new_pos);
        void setPosition(float x, float y);
        void addPosition(const sf::Vector2f pos);
        void addPosition(float x, float y);

        sf::Vector2f getSpeed() const;
        void setSpeed(const sf::Vector2f new_speed);
        void setSpeed(float x, float y);
        void setHorizontalSpeed(float new_horizontal_speed);
        void resetHorizontalSpeed();
        void setVerticalSpeed(float new_vertical_speed);
        void resetVerticalSpeed();

        sf::Vector2f getAcceleration() const;
        void setAcceleration(const sf::Vector2f new_acceleration);
        void setAcceleration(float x, float y);
        void setHorizontalAcceleration(float new_horizontal_acceleration);
        void resetHorizontalAcceleration();
        void setVerticalAcceleration(float new_vertical_acceleration);
        void resetVerticalAcceleration();

        sf::Vector2f getForce() const;
        void setForce(const sf::Vector2f force);
        void setForce(float x, float y);
        void setHorizontalForce(float new_horizontal_force);
        void resetHorizontalForce();
        void setVerticalForce(float new_vertical_force);
        void resetVerticalForce();

        const sf::Sprite& getSprite() const;
        void setSpritePos(sf::Vector2f pos);

        void setAirborne(bool new_airborne);

        bool getAirborne() const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
#endif // __ENTITY_HPP__