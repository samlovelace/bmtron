#include <vector>
#include "AI.h"

class Game
{
public:
    Game();
    ~Game();

    struct Settings
    {
        int mNumberOfSnakes; 
        std::vector<sf::Color> mColorOfEachSnake; 
        std::map<int, std::vector<std::pair<int, int>>> mNumSnakesStartingPos; 
    };
    

    void init(Game::Settings aSettingsStruct); 

    void update(); 

    void checkCollisions(); 

    void reset(); 

    /**************** GETTERS/SETTERS**********/
    std::vector<Snake*> getSnakes() {return mSnakes; }
    bool didASnakeWin(); 

private:
    std::vector<Snake*> mSnakes; 
    AI* mAI;
    Settings mSettings;  

    std::vector<int> getSnakeStartingLocation(int aNumberOfSnakes, int aSnakeId); 

};

