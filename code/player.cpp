#include "player.h"
#include "basicGun.h"
#include <iostream>

void Player::initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position){
    game = _game;
    scene = _scene;
    handle = _handle;
    position = _position;
    maxHealth = 100;
    health = 100;
    rotation = 0;
    name = "player";
    tags = OBJECT_PLAYER;
    wantedTags = OBJECT_ITEM | OBJECT_TERRAIN;
    radius = 10;
    maxMoveSpeed = 400;
    deceleration = 900;
    actionMap = NULL;
    hitbox.position = position;
    hitbox.origin = sf::Vector2f(radius, radius);
    hitbox.rotation = rotation;
    hitbox.dimensions = sf::Vector2f(radius*2, radius*2);
    initialiseItems();
    //get rid of this at some point
    Item* basicGun = new BasicGun;
    basicGun->initialise(game, scene, 0, position);
    basicGun->setOwner(this);
    std::cout << "Perk count: " << basicGun->getPerkListSize() << "\n";
    for(unsigned int i=0; i<basicGun->getPerkListSize(); i++){
        std::cout << basicGun->getPerkName(i);
        if(i != basicGun->getPerkListSize()-1){
            std::cout << ", ";
        }
    }
    std::cout << "\n";
    rightHandItem = basicGun;
}

void Player::handleEvents(){
    if(actionMap != NULL){
        if(game->input.getInputActive((*actionMap)[PLAYER_RIGHT])){
            cVelocity.x = maxMoveSpeed;
        }
        else if(game->input.getInputActive((*actionMap)[PLAYER_LEFT])){
            cVelocity.x = -maxMoveSpeed;
        }
        else{
            cVelocity.x = 0;
        }
        if(game->input.getInputActive((*actionMap)[PLAYER_DOWN])){
            cVelocity.y = maxMoveSpeed;
        }
        else if(game->input.getInputActive((*actionMap)[PLAYER_UP])){
            cVelocity.y = -maxMoveSpeed;
        }
        else{
            cVelocity.y = 0;
        }
        if(game->input.getInputActive((*actionMap)[PLAYER_ACTIVATE_R1])){
            if(rightHandItem != NULL){
                rightHandItem->activate(true);
            }
        }
        if(game->input.getInputActive((*actionMap)[PLAYER_ACTIVATE_R2])){
            if(rightHandItem != NULL){
                rightHandItem->activate(false);
            }
        }
    }
    lookAt(sf::Vector2f(sf::Mouse::getPosition(game->window)) + scene->getCameraPosition());

    updateItems();
    //reduces uncontrolled velocity toward 0, 0
    decelerate();
    hitbox.update(position, rotation, (velocity + cVelocity) * game->deltaTime());
}

void Player::update(){
    position += cVelocity * game->deltaTime();
    position += velocity * game->deltaTime();
    bounds.left = position.x - radius;
    bounds.top = position.y - radius;
    bounds.width = radius * 2;
    bounds.height = radius * 2;
}

void Player::handleCollision(SceneObject* object, Collision collision){
    if(collision.colliding || collision.willCollide){
        if(object->getTags() & OBJECT_TERRAIN){
            //move to collision
            position += collision.translation;
            velocity = velocity * 0.f;
        }
        if(object->getTags() & OBJECT_ITEM){
            inventory.push_back(dynamic_cast<Item*>(object));
            scene->uncleanRemoveObject(object->getHandle());
        }
    }
}

void Player::draw(sf::RenderTarget& target){
    sf::CircleShape circle;
    circle.setPosition(position-scene->getCameraPosition());
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setFillColor(sf::Color(255, 255, 255, 255));
    target.draw(circle);
    if(rightHandItem != NULL){
        rightHandItem->draw(target);
    }
    hitbox.draw(target);
}

void Player::cleanup(){
    if(actionMap != NULL){
        actionMap->clear();
        delete actionMap;
    }
    cleanupItems();
}

void Player::setControls(std::map<PlayerAction, std::string>* _actionMap){
    actionMap = _actionMap;
}
