#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "level.hpp"

// NOT IMPLEMENTED. Gives the list of all the continuous (made of the same element) rectangles in content_array
std::vector<sf::IntRect> Level::giveContinuousRect(){
    int x = -1;
    int y = -1;
    int width = 0;
    int height = 0;
    for (int i = 0; i < content_array.size(); i++){
        for (int j = 0; j < content_array[i].size(); j++){
            if (content_array[i][j] == 1){
                std::cout << "Non implémenté" << std::endl;
            } 
        }
    }
}

// Print the content of the content_array element to the console
void Level::printContent() const{
    for (auto line: content_array){
        for (auto element: line){
            std::cout << element << ", ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>>& Level::getContentArray() {
    return content_array;
}

Level::Level() : Level::Level(0) {}

// Hardcoded right now, later will need to load from files
Level::Level(int id){
    m_side_size = 32;
    m_size_y = 34;
    m_size_x = 60;
    content_array = std::vector<std::vector<int>>(m_size_y, std::vector<int>(m_size_x));
    sf::Texture cobble_texture;
    if (!cobble_texture.loadFromFile("assets/cobblestone1.png"))
    {
        std::cout << "Issue when loading cobble_texture" << std::endl;
    }

    // Dummy content_array to make tests
    for (int i = 0; i < 15; i++)
        content_array[i] = std::vector<int>(m_size_x, -1);

    for (int i = 0; i < content_array.size(); i++){
        for (int j = 0; j < content_array[i].size(); j++){
            continue;
        }
    }
}
