#include "floorMap.h"
#include "scene.h"
#include <fstream>

FloorMap::FloorMap(){
    initialised = false;
    objectHandles = nullptr;
    objectCount = 0;
    filename = "";
}

void FloorMap::loadMap(std::string mapFile, Scene* scene){
    if(initialised){
        unloadMap(scene);
    }

}

void FloorMap::reloadMap(Scene* scene){
    unloadMap(scene);
    loadMap(filename, scene);
}

void FloorMap::unloadMap(Scene* scene){
    if(objectHandles != nullptr){
        for(unsigned int i=0; i<objectCount; i++){
            scene->removeObject(objectHandles[i]);
        }
    }
    initialised = false;
    objectCount = 0;
    delete[] objectHandles;
    objectHandles = nullptr;
}
