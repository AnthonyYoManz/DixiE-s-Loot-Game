#include "sceneObject.h"
#include <math.h>

//Play with this?
const float SceneObject::maxVelocity = 1000.f;

int SceneObject::getTags(){
    return tags;
}

int SceneObject::getWantedTags(){
    return wantedTags;
}

sf::Vector2f SceneObject::getPosition(){
    return position;
}
sf::Vector2f SceneObject::getVelocity(){
    return velocity;
}
float SceneObject::getRotation(){
    return rotation;
}
unsigned int SceneObject::getHandle(){
    return handle;
}
#include <iostream>
Collision SceneObject::checkCollision(SceneObject* other){
    return hitbox.checkSweptSAT(other->getHitbox());
}

Hitbox SceneObject::getHitbox(){
    return hitbox;
}

void SceneObject::lookAt(sf::Vector2f point){
    rotation = (float)atan2((position.y - point.y), (point.x - position.x)) * 180.f / 3.14f;
}
void SceneObject::setVelocity(float x, float y){
    velocity.x = x;
    velocity.y = y;
    if(velocity.x > maxVelocity){
        velocity.x = maxVelocity;
    }
    else if(velocity.x < -maxVelocity){
        velocity.x = -maxVelocity;
    }
    else if(velocity.y > maxVelocity){
        velocity.y = maxVelocity;
    }
    else if(velocity.y < -maxVelocity){
        velocity.y = -maxVelocity;
    }
}
void SceneObject::changeVelocity(float x, float y){
    velocity.x += x;
    velocity.y += y;
    if(velocity.x > maxVelocity){
        velocity.x = maxVelocity;
    }
    else if(velocity.x < -maxVelocity){
        velocity.x = -maxVelocity;
    }
    else if(velocity.y > maxVelocity){
        velocity.y = maxVelocity;
    }
    else if(velocity.y < -maxVelocity){
        velocity.y = -maxVelocity;
    }
}

void SceneObject::decelerate(){
    if(velocity.x > 0){
        if(velocity.x > maxVelocity){
            velocity.x = maxVelocity;
        }
        velocity.x -= deceleration * game->deltaTime();
        if(velocity.x < 0){
            velocity.x = 0;
        }
    }
    else if(velocity.x < 0){
        if(velocity.x < -maxVelocity){
            velocity.x = -maxVelocity;
        }
        velocity.x += deceleration * game->deltaTime();
        if(velocity.x > 0){
            velocity.x = 0;
        }
    }
    if(velocity.y > 0){
        if(velocity.y > maxVelocity){
            velocity.y = maxVelocity;
        }
        velocity.y -= deceleration * game->deltaTime();
        if(velocity.y < 0){
            velocity.y = 0;
        }
    }
    else if(velocity.y < 0){
        if(velocity.y < -maxVelocity){
            velocity.y = -maxVelocity;
        }
        velocity.y += deceleration * game->deltaTime();
        if(velocity.y > 0){
            velocity.y = 0;
        }
    }
}
