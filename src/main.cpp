#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Game.h"
#include "utilities.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BM-Tron");

    // Start Screen with game options 
    // number of snakes 2,3 or 4 
    // color of snakes r,g,b,y,g,p
    // difficulty, easy, med, hard (determines how unpredictable snake ai is)

    // key is simply the number of the snake
    // value is a vector containing values for color, isUser, and difficulty
    std::map<int, std::vector<double>> gameSettings; 

    Game* game = new Game(); 

    game->init();

    while(window.isOpen())
    {
        sf::Event event; 
        while(window.pollEvent(event))
        {
            // if user hit the close button or esc key, close the game
            if(event.type == sf::Event::Closed || 
                                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close(); 
            }

            // check which arrow key was pressed 
            if(event.type == sf::Event::KeyPressed)
            {
                Snake* snake = game->getSnakes()[0];

               switch (event.key.code)
               {
                case sf::Keyboard::Up:
                    snake->setDirection(Segment::DIRECTION::UP); 
                    break;
                case sf::Keyboard::Down:
                    snake->setDirection(Segment::DIRECTION::DOWN); 
                    break; 
                case sf::Keyboard::Left: 
                    snake->setDirection(Segment::DIRECTION::LEFT); 
                    break; 
                case sf::Keyboard::Right: 
                    snake->setDirection(Segment::DIRECTION::RIGHT); 
                    break;
                default:
                    break;
               }
            }
        }

        // update all snakes 
        game->update(); 

        // check if collisions occured 
        if(game->checkCollisions())
        {
            game->reset(); 
        } 

        // normally might call this but i actually 
        // want to keep the previous drawing of the snake
        window.clear(); 

        // draw the grid 
        utils::renderGrid(window); 

        for(auto snake : game->getSnakes())
        { 
            // draw the new position of the snake's head 
            for(auto seg : snake->getSegments())
            {
                window.draw(seg->getDrawable()); 
            }
        }

        window.display(); 

        // delay to make the game playable 
        sf::sleep(sf::milliseconds(50)); 

    }
 
}