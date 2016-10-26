#include "game.h"
#include "gameState.h"
#include <cstdlib>

const float Game::maxDt = 0.1;

//primary functions
void Game::initialise(GameState* initialState){
    //window.create(sf::VideoMode::getDesktopMode(), "Equipment Test", sf::Style::Fullscreen);
    window.create(sf::VideoMode(640, 480), "Equipment Test", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(1);
    windowSize = window.getSize();
    clearColour = sf::Color(0, 0, 0, 255);
    //srand(2);
    srand(gameTimer.getElapsedTime().asMilliseconds());
    initialState->initialise(this);
    state.push_back(initialState);
    running = true;
    dt = 0;
    gameTimer.restart();
    loopTimer.restart();
}
bool Game::pollEvent(sf::Event& event){
    return window.pollEvent(event);
}
void Game::update(){
    input.cleanEvents();
    input.handleEvents(window);
    dt = loopTimer.getElapsedTime().asSeconds();
    loopTimer.restart();
    state.back()->update();
}
void Game::draw(){
    window.clear(clearColour);
    state.back()->draw(window);
    window.display();
}
void Game::quit(){
    running = false;
}
void Game::cleanup(){
    if(!running){
        window.close();
        for(unsigned int i=0; i<state.size(); i++){
            state.at(i)->cleanup();
            delete state.at(i);
        }
        state.clear();
        input.clearMaps();
    }
}

//setters
void Game::setClearColour(sf::Color colour){
    clearColour = colour;
}

//getters
bool Game::isRunning(){
    return running;
}
sf::Vector2u Game::getWindowSize(){
    return windowSize;
}
float Game::getGameTime(){
    return gameTimer.getElapsedTime().asSeconds();
}
float Game::deltaTime(){
    return dt<maxDt ? dt : maxDt;
}

