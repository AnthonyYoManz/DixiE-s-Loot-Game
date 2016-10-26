#ifndef ANT_GAME_OBJECT

#include <SFML/Graphics.hpp>
#include <string>
#include "game.h"

class GameObject{
protected:
    Game* game;
    std::string name;
public:
    std::string getName();
};

#define ANT_GAME_OBJECT
#endif // ANT_GAME_OBJECT
