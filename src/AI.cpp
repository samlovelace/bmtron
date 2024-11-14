#include "AI.h"
#include "utilities.h"


AI::AI(/* args */)
{
}

AI::~AI()
{
}

int AI::state(Snake& snake, AI::TRY tryDir, std::vector<Snake*> otherSnakes)
{
    int reward = 0; 
    Segment* head = snake.getHead(); 

    int try_x = head->x(); 
    int try_y = head->y();  

    switch (head->direction())
    {
    case Segment::DIRECTION::UP:
        switch (tryDir)
        {
        case AI::TRY::FORWARD:
            try_y += -CELL_SIZE;  
            break;
        case AI::TRY::LEFT:
            try_x += -CELL_SIZE; 
            break; 
        case AI::TRY::RIGHT: 
            try_x += CELL_SIZE; 
            break; 
        default:
            break;
        }
        break;
    case Segment::DIRECTION::DOWN: 
        switch (tryDir)
        {
        case AI::TRY::FORWARD:
            try_y += CELL_SIZE; 
            break;
        case AI::TRY::LEFT:
            try_x += CELL_SIZE; 
            break;
        case AI::TRY::RIGHT: 
            try_x += -CELL_SIZE; 
            break; 
        default:
            break;
        }
        break;
    case Segment::DIRECTION::LEFT:
        switch (tryDir)
        {
        case AI::TRY::FORWARD:
            try_x += -CELL_SIZE; 
            break;
        case AI::TRY::LEFT: 
            try_y += CELL_SIZE;  
            break;
        case AI::TRY::RIGHT: 
            try_y += -CELL_SIZE;  
            break; 
        default:
            break;
        }
        break;
    case Segment::DIRECTION::RIGHT: 
        switch (tryDir)
        {
        case AI::TRY::FORWARD:
            try_x += CELL_SIZE; 
            break;
        case AI::TRY::LEFT: 
            try_y += -CELL_SIZE; 
            break; 
        case AI::TRY::RIGHT:
            try_y += CELL_SIZE; 
            break;
        default:
            break;
        }
    
    default:
        break;
    }

    
    // dont run into yourself dummy
    for(auto seg : snake.getSegments())
    {
        if(try_x == seg->x() && try_y == seg->y())
        {
            reward += -100; 
        }
    }

    // dont hit the border
    if(try_x < MIN_X || try_x >= MAX_X)
    {
        reward += -100; 
    }

    // dont hit the other border dummy 
    if(try_y < MIN_Y || try_y >= MAX_Y)
    {
        reward += -100; 
    }

    for(auto other : otherSnakes)
    {
        if(&snake == other)
        {
            break;
        }

        for(auto seg : other->getSegments())
        {
            if(try_x == seg->x() && try_y == seg->y())
            {
                reward += -100; 
            }
        }

        int other_x = other->getHead()->x(); 
        int other_y = other->getHead()->y(); 

        // get closer to the apple, so you can eat it
        int diff_x = abs(head->x() - other_x); 
        int diff_y = abs(head->y() - other_y); 
        int try_diff_x = abs(try_x - other_x); 
        int try_diff_y = abs(try_y - other_y); 

        if(try_diff_x < diff_x)
        {
            reward += 5; 
        }
        if(try_diff_y < diff_y)
        {
            reward += 5; 
        }

    }
    
    return reward; 
}



void AI::move(Snake& snake, std::vector<Snake*> otherSnakes)
{
    // for current position of snake, try each possible direction to move
    int try_f = state(snake, AI::TRY::FORWARD, otherSnakes); 
    int try_l = state(snake, AI::TRY::LEFT, otherSnakes); 
    int try_r = state(snake, AI::TRY::RIGHT, otherSnakes); 


    // based on the scores from above, if try_f is the largest value, 
    // no need to change the direction of the snake
    if(try_f >= try_l && try_f >= try_r)
    {
        // no change in direction
    }
    else if (try_l > try_r)
    {
        turnSnakeLeft(snake);  
    }
    else
    {
        turnSnakeRight(snake);  
    }
}

void AI::turnSnakeLeft(Snake& snake)
{
    Snake* snakeptr = &snake; 

    Segment::DIRECTION currentDir = snakeptr->getHead()->direction(); 

    switch (currentDir)
    {
    case Segment::DIRECTION::UP:
        snakeptr->setDirection(Segment::DIRECTION::LEFT);
        break;
    case Segment::DIRECTION::DOWN: 
        snakeptr->setDirection(Segment::DIRECTION::RIGHT); 
        break; 
    case Segment::DIRECTION::LEFT:
        snakeptr->setDirection(Segment::DIRECTION::DOWN); 
        break; 
    case Segment::DIRECTION::RIGHT:
        snakeptr->setDirection(Segment::DIRECTION::UP); 
        break; 
    default:
        break;
    }
}


void AI::turnSnakeRight(Snake& snake)
{
    Snake* snakeptr = &snake; 

    Segment::DIRECTION currentDir = snakeptr->getHead()->direction(); 

    switch (currentDir)
    {
    case Segment::DIRECTION::UP:
        snakeptr->setDirection(Segment::DIRECTION::RIGHT);
        break;
    case Segment::DIRECTION::DOWN: 
        snakeptr->setDirection(Segment::DIRECTION::LEFT); 
        break; 
    case Segment::DIRECTION::LEFT:
        snakeptr->setDirection(Segment::DIRECTION::UP); 
        break; 
    case Segment::DIRECTION::RIGHT:
        snakeptr->setDirection(Segment::DIRECTION::DOWN); 
        break; 
    default:
        break;
    }

}