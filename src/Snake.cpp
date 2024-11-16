
#include "Snake.h"
#include <iostream> 


Snake::Snake(sf::Color aColor, int aSnakeId) : mAlive(true), mColor(aColor), mNumSegments(3), mId(aSnakeId), mSegments(), mUserControlled(false)
{
}

Snake::~Snake()
{
}

void Snake::init(int x, int y)
{
    Segment* seg = new Segment(CELL_SIZE, CELL_SIZE); 

    seg->setColor(mColor); 
    seg->setPosition(x,y); 
    seg->setDirection(Segment::DIRECTION::UP); 

    mHead = seg; 

    mSegments.push_back(seg); 
}

void Snake::update()
{
    // get the current head of the snake 
    Segment* head = mSegments.front(); 

    // new segment to prepend to the snake 
    Segment* seg = new Segment(CELL_SIZE, CELL_SIZE);  
    seg->setColor(mColor); 
    seg->setDirection(head->direction()); 

    // based on the current direction of the snake, determine the new head location
    switch (head->direction())
    {
    case Segment::DIRECTION::UP:
        seg->setPosition(head->x(), head->y() - CELL_SIZE); 
        break;
    case Segment::DIRECTION::DOWN: 
        seg->setPosition(head->x(), head->y() + CELL_SIZE);
        break; 
    case Segment::DIRECTION::LEFT: 
        seg->setPosition(head->x() - CELL_SIZE, head->y()); 
        break; 
    case Segment::DIRECTION::RIGHT: 
        seg->setPosition(head->x() + CELL_SIZE, head->y());
        break; 
    default:
        break;
    }

    // prepend the new head of the snake 
    mSegments.push_front(seg); 
    mHead = mSegments.front(); 
}

bool Snake::collidedWithGrid()
{
    if(mHead->x() < MIN_X || mHead->x() >= MAX_X || mHead->y() < MIN_Y || mHead->y() >= MAX_Y)
    {
        return true; 
    }

    return false; 
}

bool Snake::collidedWithSelf()
{
    std::list<Segment*>::iterator it = mSegments.begin(); 
    ++it; 

    // check to make sure current head hasnt collided with its own body 
    for(; it != mSegments.end(); it++)
    {
        if(mHead->x() == (*it)->x() && mHead->y() == (*it)->y())
        {
            return true; 
        }
    }

    return false; 

}

bool Snake::collidedWithOther(Snake& other)
{
    for(auto seg : other.getSegments())
    {
        if(mHead->x() == seg->x() && mHead->y() == seg->y())
        {
            return true; 
        }
    }

    return false; 

}

void Snake::reset(std::vector<int> aStartingLocation)
{
    mSegments.clear();
    
    for(auto seg : mSegments)
    {
        delete seg; 
    }
 
    revive(); 
    init(aStartingLocation[0], aStartingLocation[1]);   
}