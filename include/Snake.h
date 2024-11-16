#include "Segment.h"
#include <list>

class Snake
{
public:
    Snake(sf::Color aColor, int aSnakeId);
    ~Snake();
    void init(int x, int y);
    void update(); 
    void reset(std::vector<int> aStartingLocation); 
    bool collidedWithGrid(); 
    bool collidedWithSelf(); 
    bool collidedWithOther(Snake& other); 

    /**********GETTERS/SETTERS *************/
    Segment* getHead() {return mSegments.front();}
    std::list<Segment*> getSegments() {return mSegments;}
    void setDirection(Segment::DIRECTION aDir){mSegments.front()->setDirection(aDir);}
    void setSnakeNumber(int aNum) {mId = aNum;}
    bool isUserControlled() {return mUserControlled; }
    void setUserControlled(bool aFlag) {mUserControlled = aFlag; }
    int getId() {return mId; }
    bool isAlive() {return mAlive; }
    void kill() {mAlive = false;}
    void revive() {mAlive = true; }

private:
    
    std::list<Segment*> mSegments; 
    int mNumSegments; 
    Segment* mHead; 
    sf::Color mColor; 
    int mId; 
    bool mUserControlled; 
    bool mAlive; 


};