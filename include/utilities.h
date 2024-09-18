#include "SFML/Graphics.hpp"
#include "constants.h"


namespace utils
{
    inline void renderGrid(sf::RenderWindow& window)
    {
        std::vector<sf::RectangleShape> grid;
            for (int i = 0; i < GRID_SIZE+2; i++) {
                for (int j = 0; j < GRID_SIZE+2; j++) {
                    if(i== 0 || i == GRID_SIZE+1 || j == 0 || j == GRID_SIZE+1)
                    {
                        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)); // Slightly smaller for grid lines
                        
                        float x_position = GRID_X + ((i - 1) * CELL_SIZE); // Shift grid to the left by one CELL_SIZE
                        float y_position = GRID_Y + ((j - 1) * CELL_SIZE); // Shift grid upwards by one CELL_SIZE

                        cell.setPosition(x_position, y_position);   // Use offset for centering
                        cell.setFillColor(sf::Color::Black);  // Cells are black
                        cell.setOutlineThickness(1);          // Create a grid-like outline
                        cell.setOutlineColor(sf::Color::White);
                        grid.push_back(cell);
                    }
                    
                }
            }        

            for(auto& cell : grid)
            {
                window.draw(cell); 
            }
    }
}