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
        int m_tile_size;

        // Contains all the infos about the elements in the level
        std::vector<std::vector<int>> m_content_array;
        TileMap m_tile_map;
        sf::Sprite level_sprite;


    public:
        // Print the content of the content_array element to the console
        void printContent() const;
        const std::vector<std::vector<int>>& getContentArray() const;
        int getTileSize() const;
        const TileMap& getTileMap() const;

        Level();
        Level(int id);
        // ~Level();
};

#endif