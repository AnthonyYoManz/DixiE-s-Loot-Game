#include "scene.h"
#include "sceneObject.h"

void Scene::addObject(SceneObject* object, sf::Vector2f position){
    if(currentHandle == 0){
        currentHandle = 1;
    }
    object->initialise(game, this, currentHandle, position);
    objectList.push_back(object);
    currentHandle++;
}
void Scene::removeObject(unsigned int handle){
    removalList.push_back(handle);
}
void Scene::uncleanRemoveObject(unsigned int handle){
    uncleanRemovalList.push_back(handle);
}
void Scene::moveCamera(float x, float y){
    cameraPosition.x += x;
    cameraPosition.y += y;
}
void Scene::offsetCamera(float x, float y){
    cameraOffset.x += x;
    cameraOffset.y += y;
}
sf::Vector2f Scene::getCameraPosition(){
    return cameraPosition + cameraOffset;
}
unsigned int Scene::getObjectCount(){
    return objectList.size();
}

SceneObject* Scene::getObjectByID(unsigned int objectID){
    if(objectID < objectList.size()){
        return objectList.at(objectID);
    }
    return NULL;
}

SceneObject* Scene::getObjectByHandle(unsigned int handle){
    if(handle != 0){
        for(SceneObject* object : objectList){
            if(object->getHandle() == handle){
                return object;
            }
        }
    }
    return NULL;
}

void Scene::removeObjectFromList(unsigned int handle){
    if(handle != 0){
        for(unsigned int i=0; i<objectList.size(); i++){
            if(objectList.at(i)->getHandle() == handle){
                objectList.at(i)->cleanup();
                delete objectList.at(i);
                objectList.erase(objectList.begin()+i);
                break;
            }
        }
    }
}
void Scene::processRemovalList(){
    for(unsigned int i=0; i<removalList.size(); i++){
        removeObjectFromList(removalList.at(i));
    }
    removalList.clear();
}
void Scene::processUncleanRemovalList(){
    for(unsigned int i=0; i<uncleanRemovalList.size(); i++){
        unsigned int handle = uncleanRemovalList.at(i);
        if(handle != 0){
            for(unsigned int i=0; i<objectList.size(); i++){
                if(objectList.at(i)->getHandle() == handle){
                    objectList.erase(objectList.begin()+i);
                    break;
                }
            }
        }
    }
}
