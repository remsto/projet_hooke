#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "level.hpp"


// Print the content of the content_array element to the console
void Level::printContent() const{
    for (auto line: content_array){
        for (auto element: line){
            std::cout << element << ", ";
        }
        std::cout << std::endl;
    }
}

const std::vector<std::vector<int>>& Level::getContentArray() const{
    return content_array;
}

int Level::getTileSize() const{
    return m_tile_size;
}

Level::Level() : Level::Level(0) {}

// Hardcoded right now, later will need to load from files
Level::Level(int id){
    m_tile_size = 32;
    m_size_y = 34;
    m_size_x = 60;
    content_array = std::vector<std::vector<int>>(m_size_y, std::vector<int>(m_size_x));
    sf::Texture cobble_texture;
    if (!cobble_texture.loadFromFile("assets/cobblestone1.png"))
    {
        std::cout << "Issue when loading cobble_texture" << std::endl;
    }

    // Dummy content_array to make tests
    for (unsigned int i = 0; i < 15; i++)
        content_array[i] = std::vector<int>(m_size_x, -1);

    for (unsigned int i = 0; i < content_array.size(); i++){
        for (unsigned int j = 0; j < content_array[i].size(); j++){
            continue;
        }
    }
}
