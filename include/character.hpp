#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Character : public Entity {
        
    private:
        float m_base_force;
        float m_base_jump;


    public:
        float getBaseForce() const;
        float getBaseJump() const;
        Character();
        // ~Character();
};

#endif