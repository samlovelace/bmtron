#ifndef AI_H
#define AI_H

#include "Snake.h"

class AI
{
public:
    AI(/* args */);
    ~AI();

    /** 
     * TRY - enum for each direction for the AI to "try"
     */
    enum class TRY
    {
        FORWARD, 
        LEFT, 
        RIGHT
    }; 

    /** 
     * @brief move() determines the next direction of the snake
     */
    void move(Snake& snake, std::vector<Snake*> otherSnakes); 

    /** 
     * @brief state() determines the reward for each direction the snake could move 
     *        based on its current position 
     */
    int state(Snake& snake, TRY tryDir, std::vector<Snake*> otherSnakes); 

    /** 
     * @brief turnSnakeLeft() turns the snake to the left based on its current direction
     */
    void turnSnakeLeft(Snake& snake); 

    /** 
     * @brief turnSnakeRight() turns the snake to the right based on its current direction
     */
    void turnSnakeRight(Snake& snake); 

private:
    /* data */

};

#endif // AI_H

