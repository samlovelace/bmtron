
#include "Game.h"

Game::Game() : mSnakes(), mAI(new AI())
{
}

Game::~Game()
{
}


void Game::init()
{
    // do for any configured number of snakes 
    Snake* snake = new Snake(sf::Color::Green);

    snake->init(X1, Y1); 
    snake->setSnakeNumber(1); 
    snake->setUserControlled(true); 

    mSnakes.push_back(snake);  

    Snake* other = new Snake(sf::Color::Blue); 
    other->init(X2, Y2); 
    other->setSnakeNumber(2); 
    other->setUserControlled(false); 
    mSnakes.push_back(other); 

    Snake* another = new Snake(sf::Color::Magenta); 
    another->init(300, 300); 
    another->setSnakeNumber(3); 
    another->setUserControlled(false); 

    mSnakes.push_back(another); 

}

void Game::update()
{
    for(Snake* snake : mSnakes)
    {
        if(!snake->isUserControlled())
        {
            mAI->move(*snake, mSnakes); 
        }

        snake->update();
    }

}

bool Game::checkCollisions()
{
    for(Snake* snake : mSnakes)
    {
        if(snake->collidedWithGrid() || snake->collidedWithSelf())
        {
            return true; 
        }

        for(Snake* other : mSnakes)
        {
            if(snake != other)
            {
                if(snake->collidedWithOther(*other))
                {
                    return true; 
                }
            }
        }
    }

    return false; 
}

void Game::reset()
{
    for(auto snake : mSnakes)
    {
        snake->reset(); 
    }
}

