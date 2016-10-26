#include "vacuumModifier.h"
#include "sceneObject.h"

void VacuumModifier::initialise(Game* _game, Scene* _scene){
    game = _game;
    scene = _scene;
}

void VacuumModifier::update(){
    for(unsigned int i=0; i<scene->getObjectCount(); i++){
        SceneObject* object = scene->getObjectByID(i);
        sf::Vector2f displacement = object->getPosition() - bullet->getPosition();
        float magnitude = sqrtf(displacement.x * displacement.x + displacement.y * displacement.y);
        if(magnitude<vacuumRadius && object->getHandle()!=bullet->getHandle() && object->getHandle()!=bullet->ownerHandle){
            sf::Vector2f unitVector(0, 0);
            if(magnitude!=0){
                unitVector = displacement/magnitude;
            }
            unitVector *= -vacuumPower;
            object->changeVelocity(unitVector.x * game->deltaTime(), unitVector.y * game->deltaTime());
        }
    }
}

void VacuumModifier::draw(sf::RenderTarget& target){
}

void VacuumModifier::cleanup(){
}
