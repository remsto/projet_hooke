#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "level.hpp"


void Level::printContent() const{
    for (auto line: m_content_array){
        for (auto element: line){
            std::cout << element << ", ";
        }
        std::cout << std::endl;
    }
}

const std::vector<std::vector<LevelTile>>& Level::getContentArray() const{
    return m_content_array;
}

int Level::getTileSize() const{
    return m_tile_size;
}

const TileMap& Level::getTileMap() const{
    return m_tile_map;
}

Level::Level() : Level::Level(0) {}

// Hardcoded right now, later will need to load from files
Level::Level(int id){
    m_tile_size = 32;
    m_size_y = 34;
    m_size_x = 60;
    m_content_array = std::vector<std::vector<LevelTile>>(m_size_y, std::vector<LevelTile>(m_size_x));
    sf::Texture cobble_texture;
    if (!cobble_texture.loadFromFile("assets/cobblestone1.png"))
    {
        std::cout << "Issue when loading cobble_texture" << std::endl;
    }

    // Dummy content_array to make tests
    for (unsigned int i = 0; i < m_size_y; i++){
        for (unsigned int j = 0; j < m_size_x; j++){
            m_content_array[i][j] = ((j > 1 && i < 15 && i!=10) || (j > 35 && j < 37 /* ||  (i == 10  && (j % 3 == 0 || j%3 == 1) */ ) ) ? LevelTile::Air : LevelTile::Stone;
        }
    }

    // std::cout << LevelTile::air << " " << LevelTile::stone << " " << LevelTile::deadzone << std::endl;


    if (!m_tile_map.load("assets/cobblestone1.png", sf::Vector2u(32, 32), m_content_array))
        std::cout << "Issue loading the tile map" << std::endl;;
}
