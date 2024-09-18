#include <vector>
#include "AI.h"

class Game
{
public:
    Game();
    ~Game();

    void init(); 

    void update(); 

    bool checkCollisions(); 

    void reset(); 

    /**************** GETTERS/SETTERS**********/
    std::vector<Snake*> getSnakes() {return mSnakes; }

private:
    std::vector<Snake*> mSnakes; 
    AI* mAI; 

};

