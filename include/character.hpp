#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "hook.hpp"

class Character : public Entity {
        
    private:
        float m_base_force;
        float m_base_jump;
        bool m_is_running;
        Hook m_hook;

    public:
        float getBaseForce() const;
        float getBaseJump() const;
        bool isRunning() const;
        void setRunning(const bool is_running);
        Character();
        // ~Character();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif