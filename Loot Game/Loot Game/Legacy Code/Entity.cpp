#include "entity.h"
void Entity::initialiseItems(){
    rightHandItem = NULL;
    leftHandItem = NULL;
    headItem = NULL;
    bodyItem = NULL;
    miscItem = NULL;
}
void Entity::updateItems(){
    if(rightHandItem!=NULL){
        rightHandItem->update();
    }
    if(leftHandItem!=NULL){
        rightHandItem->update();
    }
    if(headItem!=NULL){
        rightHandItem->update();
    }
    if(bodyItem!=NULL){
        rightHandItem->update();
    }
    if(miscItem!=NULL){
        rightHandItem->update();
    }
}
void Entity::cleanupItems(){
    delete rightHandItem;
    rightHandItem = NULL;
    delete leftHandItem;
    leftHandItem = NULL;
    delete headItem;
    headItem = NULL;
    delete bodyItem;
    bodyItem = NULL;
    delete miscItem;
    miscItem = NULL;
}

float Entity::getHealth(){
    return health;
}

void Entity::inflictDamge(float damage){
    health -= damage;
}

bool Entity::onScreen(){
    sf::Vector2f camPos = scene->getCameraPosition();
    if(bounds.left > camPos.x + game->getWindowSize().x){
        return false;
    }
    else if(bounds.left + bounds.width < camPos.x){
        return false;
    }
    else if(bounds.top + bounds.height < camPos.y){
        return false;
    }
    else if(bounds.top > camPos.y + game->getWindowSize().y){
        return false;
    }
    return true;
}
