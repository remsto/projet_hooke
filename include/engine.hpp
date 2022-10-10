#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "character.hpp"

// Physical engine for the game. Should contain the world and the entities 
class Engine {
    private:
        // Physics constants

        // Frottements fluides
        float m_nu;

        Level m_level;
        Character m_character;
        sf::View m_main_view;
    
    public:
        // General update of the engine. Updates position, speed, acceleration and collisions of all entities and main_view
        void updatePhysics();

        // Reset of the consts at each beginning of the loop
        void resetLoopConsts();

        // Check if the entity is airborne in the engine level
        bool checkAirborne(const Entity& entity) const;

        // Sticks an entity to the ground
        void stickGround(Entity& entity) const;

        // Handle the keyboard event if it happened
        void handleEvent(sf::Event event);

        // Check if the entity is colliding with a tile of the level
        bool checkCollision(const Entity& entity) const;

        // Handle the collisions of an entity (not enter in walls)
        void handleCollision(Entity& entity);

        // Gives the coords of the position in the tile map
        sf::Vector2i getTilePos(const sf::Vector2f pos) const;

        // Gives the character. Should not be modified outside of the engine
        const Character& getCharacter() const;

        // Gives the level. Should not be modified outside of the engine
        const Level& getLevel() const;

        const sf::View& getMainView() const;

        Engine();

        Engine(Level& level, Character& character, sf::View& view);
};

#endif // __ENGINE_HPP__