#ifndef ANT_GAME

#include <SFML/Graphics.hpp>
#include <vector>
#include "input.h"

class GameState;

class Game{
private:
    bool running;
    sf::Vector2u windowSize;
    std::vector<GameState*> state;
    sf::Clock gameTimer;
    sf::Clock loopTimer;
    static const float maxDt;
    float dt;
    sf::Color clearColour;
public:
    sf::RenderWindow window;
    Input input;

    //primary functions
    void initialise(GameState* initialState);
    bool pollEvent(sf::Event& event);
    void update();
    void draw();
    void quit();
    void cleanup();

    //setters
    void setClearColour(sf::Color colour);
    //getters
    bool isRunning();
    sf::Vector2u getWindowSize();
    float getGameTime();
    float deltaTime();
};

#define ANT_GAME
#endif // ANT_GAME
