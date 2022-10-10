#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Character : public Entity {
        
    private:
        float m_base_force;


    public:
        float getBaseForce() const;
        Character();
        // ~Character();
};

#endif