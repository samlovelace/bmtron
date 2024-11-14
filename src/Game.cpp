
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

    }

    return start; 
}

