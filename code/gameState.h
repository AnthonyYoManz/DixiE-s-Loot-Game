#ifndef ANT_GAME_STATE

#include <SFML/Graphics.hpp>
#include "game.h"

class GameState{
protected:
    Game* game;
public:
    virtual ~GameState(){};
    virtual void initialise(Game* game) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual void cleanup() = 0;
};

#define ANT_GAME_STATE
#endif // ANT_GAME_STATE
