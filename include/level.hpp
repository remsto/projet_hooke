#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "tile_map.hpp"

class Level {
    private:
        int m_size_y;
        int m_size_x;
        // Defines the number of pixels of a squared sprite
        int m_side_size;

        // Contains all the infos about the elements in the level
        std::vector<std::vector<int>> content_array;
        TileMap map;
        sf::Sprite level_sprite;


    public:
        void printContent() const;
        std::vector<sf::IntRect> giveContinuousRect();
        std::vector<std::vector<int>>& getContentArray();

        Level();
        Level(int id);
        // ~Level();
};

#endif