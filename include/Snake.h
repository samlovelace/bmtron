#include "Segment.h"
#include <list>

class Snake
{
public:
    Snake(sf::Color aColor);
    ~Snake();
    void init(int x, int y);
    void update(); 
    void reset(); 
    bool collidedWithGrid(); 
    bool collidedWithSelf(); 
    bool collidedWithOther(Snake& other); 

    /**********GETTERS/SETTERS *************/
    Segment* getHead() {return mSegments.front();}
    std::list<Segment*> getSegments() {return mSegments;}
    void setDirection(Segment::DIRECTION aDir){mSegments.front()->setDirection(aDir);}
    void setSnakeNumber(int aNum) {mSnakeNum = aNum;}
    bool isUserControlled() {return mUserControlled; }
    void setUserControlled(bool aFlag) {mUserControlled = aFlag; }

private:
    
    std::list<Segment*> mSegments; 
    int mNumSegments; 
    Segment* mHead; 
    sf::Color mColor; 
    int mSnakeNum; 
    bool mUserControlled; 


};