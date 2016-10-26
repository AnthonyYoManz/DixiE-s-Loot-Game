#include "testScene.h"
#include <map>
#include <cstdlib>
#include "sceneObject.h"
#include "player.h"
#include "perk.h"
#include "tile.h"

#include <iostream>
void TestScene::initialise(Game* _game){
    Perk::initialiseAll();
    game = _game;
    game->input.registerInput("exit", sf::Event::Closed);
    game->input.registerInput("exit", sf::Keyboard::Escape);

    game->input.registerInput("p1right", sf::Keyboard::D);
    game->input.registerInput("p1left", sf::Keyboard::A);
    game->input.registerInput("p1up", sf::Keyboard::W);
    game->input.registerInput("p1down", sf::Keyboard::S);
    game->input.registerInput("p1r1", sf::Mouse::Left);
    game->input.registerInput("p1r2", sf::Keyboard::Q);
    game->input.registerInput("p1l1", sf::Mouse::Right);
    game->input.registerInput("p1l2", sf::Keyboard::E);

    std::map<PlayerAction, std::string>* p1ActionMap = new std::map<PlayerAction, std::string>;
    (*p1ActionMap)[PLAYER_UP] = "p1up";
    (*p1ActionMap)[PLAYER_DOWN] = "p1down";
    (*p1ActionMap)[PLAYER_LEFT] = "p1left";
    (*p1ActionMap)[PLAYER_RIGHT] = "p1right";
    (*p1ActionMap)[PLAYER_ACTIVATE_R1] = "p1r1";
    (*p1ActionMap)[PLAYER_ACTIVATE_R2] = "p1r2";
    (*p1ActionMap)[PLAYER_ACTIVATE_L1] = "p1l1";
    (*p1ActionMap)[PLAYER_ACTIVATE_L2] = "p1l2";
    Player* player = new Player;
    addObject(player, sf::Vector2f(game->getWindowSize().x/2, game->getWindowSize().y/2));
    player->setControls(p1ActionMap);

    Player* eplayer = new Player;
    addObject(eplayer, sf::Vector2f(game->getWindowSize().x/2, game->getWindowSize().y/2+100));

    Tile* tile = new Tile;
    addObject(tile, sf::Vector2f(80, 150));
}
void TestScene::update(){
    processRemovalList();
    if(game->input.getInputActivated("exit")){
        game->quit();
    }
    for(unsigned int i=0; i<objectList.size(); i++){
        objectList.at(i)->handleEvents();
    }
    for(unsigned int i=0; i<objectList.size(); i++){
        sf::Vector2f objPos;
        objPos = objectList.at(i)->getPosition();
        //i hope to never have to touch this again
        if(!(objPos.x < cameraPosition.x - game->getWindowSize().x ||
           objPos.x > cameraPosition.x + game->getWindowSize().x * 2 ||
           objPos.y < cameraPosition.y - game->window.getSize().y ||
           objPos.y > cameraPosition.y + game->getWindowSize().y * 2)){
            for(unsigned int j=0; j<objectList.size(); j++){
                if(i!=j){
                    if(objectList.at(i)->getWantedTags() & objectList.at(j)->getTags()){
                        objPos = objectList.at(j)->getPosition();
                        Collision collisionInfo = objectList.at(i)->checkCollision(objectList.at(j));
                        if((collisionInfo.willCollide || collisionInfo.colliding)){
                            objectList.at(i)->handleCollision(objectList.at(j), collisionInfo);
                        } //WHEEEEE
                    } //WHEEEEEEEEE
                } //EEEEEEEEEEEEEEE
            } //EEEEEEEEEEEEEEEEEEE
        } //EEEEEEEEEEEEEEEEEEEEEEE
    } //EEEEEEEEEEEEEEEEEEEEEEEEEEE
    for(unsigned int i=0; i<objectList.size(); i++){
        objectList.at(i)->update();
    }
}

void TestScene::draw(sf::RenderTarget& target){
    for(unsigned int i=0; i<objectList.size(); i++){
        if(objectList.at(i)->onScreen()){
            objectList.at(i)->draw(target);
        }
    }
}
void TestScene::cleanup(){
    for(unsigned int i=0; i<objectList.size(); i++){
        objectList.at(i)->cleanup();
        delete objectList.at(i);
    }
    game->input.clearMaps();
    Perk::cleanup();
}
