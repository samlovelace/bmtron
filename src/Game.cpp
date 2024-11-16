
#include "Game.h"
#include <iostream>

Game::Game() : mSnakes(), mAI(new AI())
{
}

Game::~Game()
{
}


void Game::init(Game::Settings aSettingsStruct)
{
    // save off for later use
    mSettings = aSettingsStruct; 

    // setup each snake 
    for(int snakeId = 0; snakeId < aSettingsStruct.mNumberOfSnakes; snakeId++)
    { 
        Snake* snake = new Snake(aSettingsStruct.mColorOfEachSnake[snakeId], snakeId); 

        std::vector<int> start = getSnakeStartingLocation(aSettingsStruct.mNumberOfSnakes, snakeId); 
        snake->init(start[0], start[1]); 

        if(0 == snakeId)
        {
            snake->setUserControlled(true); 
        }
        else{
            snake->setUserControlled(false); 
        }

        mSnakes.push_back(snake); 
    }
}

void Game::update()
{
    for(Snake* snake : mSnakes)
    {
        if(!snake->isAlive())
        {
            continue;
        }

        if(!snake->isUserControlled())
        {
            mAI->move(*snake, mSnakes); 
        }

        snake->update();
    }

}

void Game::checkCollisions()
{
    for(Snake* snake : mSnakes)
    {
        // dont need to check collisions for a dead snake
        if(!snake->isAlive())
        {
            continue; 
        }
        
        if(snake->collidedWithGrid() || snake->collidedWithSelf())
        {
            snake->kill(); 
            continue;
        }

        for(Snake* other : mSnakes)
        {
            if(snake != other)
            {
                if(snake->collidedWithOther(*other))
                {
                    snake->kill(); 
                    continue;  
                }
            }
        }
    }
}

void Game::reset()
{
    for(auto snake : mSnakes)
    {
        std::vector<int> start = getSnakeStartingLocation(mSettings.mNumberOfSnakes, snake->getId());
        snake->reset(start); 
    }
}

bool Game::didASnakeWin()
{
    int numSnakesAlive = 0; 
    for(auto snake : mSnakes)
    {
        // need to check that only one snake is still alive, all others are dead 
        if(snake->isAlive() && numSnakesAlive++ > 1)
        {
            return false; 
        }
    }

    return true; 
}

std::vector<int> Game::getSnakeStartingLocation(int aNumberOfSnakes, int aSnakeId)
{
    std::vector<int> start; 

    if(2 == aNumberOfSnakes)
    {
        if(0 == aSnakeId)
        {
            start = {X1, Y1}; 
        }
        if(1 == aSnakeId)
        {
            start = {X2, Y2};
        }

    }
    else if (4 == aNumberOfSnakes)
    {
        // TODO: determine the starting locations of the 4 snakes and add here
        if(0 == aSnakeId)
        {
            start = {(MIN_X + MAX_X)/4, (MIN_Y + MAX_Y)/4}; 
        }
        else if (1 == aSnakeId)
        {
            start = {(MIN_X + MAX_X)/4, 3*(MIN_Y + MAX_Y)/4};
        }
        else if (2 == aSnakeId)
        {
            start = {3*(MIN_X + MAX_X)/4, (MIN_Y + MAX_Y)/4}; 
        }
        else if (3 == aSnakeId)
        {
            start = {3*(MIN_X + MAX_X)/4, 3*(MIN_Y + MAX_Y)/4}; 
        }
    }

    return start; 
}

