#include "hitbox.h"
#include "sceneObject.h"
#include <math.h>
#include <limits>
#include <iostream>

void Hitbox::update(sf::Vector2f _position, float _rotation, sf::Vector2f _velocity){
    position = _position;
    rotation = -_rotation;
    velocity = _velocity;
}

bool Hitbox::checkAABB(Hitbox other){
    float thisCenterX = position.x - origin.x + dimensions.x/2;
    float otherCenterX = other.position.x - other.origin.x + other.dimensions.x/2;
    float thisCenterY = position.y - origin.y + dimensions.y/2;
    float otherCenterY = other.position.y - other.origin.y + other.dimensions.y/2;
    bool xCollision = (std::abs(thisCenterX - otherCenterX) <= dimensions.x/2 + other.dimensions.x/2);
    bool yCollision = (std::abs(thisCenterY - otherCenterY) <= dimensions.y/2 + other.dimensions.y/2);
    return xCollision && yCollision;
}

sf::Vector2f Hitbox::getCenter(){
    sf::Vector2f center = sf::Vector2f(position.x - origin.x + dimensions.x/2, position.y - origin.y + dimensions.y/2);
    sf::Transform transformation = sf::Transform::Identity;
    transformation.rotate(rotation, position);
    center = transformation * center;
    return center;
}

sf::Vector2f* Hitbox::getVertices(){
    sf::Vector2f* vertices = new sf::Vector2f[4];
    vertices[0] = sf::Vector2f(position.x - origin.x, position.y - origin.y);
    vertices[1] = sf::Vector2f(position.x - origin.x + dimensions.x, position.y - origin.y);
    vertices[2] = sf::Vector2f(position.x - origin.x + dimensions.x, position.y - origin.y + dimensions.y);
    vertices[3] = sf::Vector2f(position.x - origin.x , position.y - origin.y + dimensions.y);
    sf::Transform transformation = sf::Transform::Identity;
    transformation.rotate(rotation, position);
    for(int i=0; i<4; i++){
        vertices[i] = transformation * vertices[i];
    }
    return vertices;
}

void Hitbox::getMinMaxProjectionsOnAxis(sf::Vector2f axis,
                                        sf::Vector2f* verts, float& minPos, float& maxPos,
                                        sf::Vector2f* otherVerts, float& otherMinPos, float& otherMaxPos){
    for(int j=0; j<4; j++){ //for each point of first hitbox
        float pos = verts[j].x * axis.x + verts[j].y * axis.y;
        if(pos > maxPos) maxPos = pos;
        if(pos < minPos) minPos = pos;
    }
    for(int j=0; j<4; j++){ //for each point of other hitbox
        float pos = otherVerts[j].x * axis.x + otherVerts[j].y * axis.y;
        if(pos > otherMaxPos) otherMaxPos = pos;
        if(pos < otherMinPos) otherMinPos = pos;
    }
}

float Hitbox::getMinMaxDistance(float minPos, float maxPos, float otherMinPos, float otherMaxPos)
{
    if(minPos < otherMinPos)
    {
        return otherMinPos - maxPos;
    }
    return minPos - otherMaxPos;
}

bool Hitbox::checkSAT(Hitbox other){

    sf::Vector2f* verts = getVertices();
    sf::Vector2f* otherVerts = other.getVertices();

    for(int i=0; i<4; i++)
    { //for each line of first hitbox
        sf::Vector2f dir = sf::Vector2f(verts[(i+1)%4].x - verts[i].x, verts[(i+1)%4].y - verts[i].y);
        sf::Vector2f normal = sf::Vector2f(dir.y, -dir.x);
        normal /= sqrtf(normal.x * normal.x + normal.y * normal.y);
        float minPos = std::numeric_limits<float>::max(), maxPos = -std::numeric_limits<float>::max();
        float otherMinPos = minPos, otherMaxPos = maxPos;
        getMinMaxProjectionsOnAxis(normal, verts, minPos, maxPos, otherVerts, otherMinPos, otherMaxPos);
        if(!((maxPos > otherMinPos && maxPos < otherMaxPos) || (minPos > otherMinPos && minPos < otherMaxPos)))
        {
            return false;
        }
    }
    for(int i=0; i<4; i++)
    { //for each line of other hitbox
        sf::Vector2f dir = sf::Vector2f(otherVerts[(i+1)%4].x - otherVerts[i].x, otherVerts[(i+1)%4].y - otherVerts[i].y);
        sf::Vector2f normal = sf::Vector2f(dir.y, -dir.x);
        normal /= sqrtf(normal.x * normal.x + normal.y * normal.y);
        float minPos = std::numeric_limits<float>::max(), maxPos = -std::numeric_limits<float>::max();
        float otherMinPos = minPos, otherMaxPos = maxPos;
        getMinMaxProjectionsOnAxis(normal, verts, minPos, maxPos, otherVerts, otherMinPos, otherMaxPos);
        if(!((maxPos > otherMinPos && maxPos < otherMaxPos) || (minPos > otherMinPos && minPos < otherMaxPos)))
        {
            return false;
        }
    }
    delete verts;
    delete otherVerts;
    return true;
}

Collision Hitbox::checkSweptSAT(Hitbox other){
    Collision collision;
    collision.colliding = true;
    collision.willCollide = true;
    collision.translation = sf::Vector2f(0, 0);

    float intervalDistance = std::numeric_limits<float>::max();
    sf::Vector2f translationAxis = sf::Vector2f(0, 0);

    sf::Vector2f relativeVelocity = velocity - other.velocity;

    sf::Vector2f* verts = getVertices();
    sf::Vector2f* otherVerts = other.getVertices();
    sf::Vector2f edges[8];
    for(int i=0; i<4; i++){
        edges[i] = sf::Vector2f(verts[(i+1)%4].x - verts[i].x, verts[(i+1)%4].y - verts[i].y);
    }
    for(int i=0; i<4; i++){
        edges[i+4] = sf::Vector2f(otherVerts[(i+1)%4].x - otherVerts[i].x, otherVerts[(i+1)%4].y - otherVerts[i].y);
    }
    for(int i=0; i<8; i++){
        sf::Vector2f dir = edges[i];
        sf::Vector2f normal = sf::Vector2f(dir.y, -dir.x);
        normal /= sqrtf(normal.x * normal.x + normal.y * normal.y);
        float minPos = std::numeric_limits<float>::max(), maxPos = -std::numeric_limits<float>::max();
        float otherMinPos = minPos, otherMaxPos = maxPos;
        getMinMaxProjectionsOnAxis(normal, verts, minPos, maxPos, otherVerts, otherMinPos, otherMaxPos);
        if(getMinMaxDistance(minPos, maxPos, otherMinPos, otherMaxPos) > 0){
            collision.colliding = false;
        }
        float velocityProjection = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

        if(velocityProjection < 0){
            minPos += velocityProjection;
        }
        else{
            maxPos += velocityProjection;
        }
        float velIntervalDistance = getMinMaxDistance(minPos, maxPos, otherMinPos, otherMaxPos);
        if(velIntervalDistance > 0){
            collision.willCollide = false;
        }
        if(!collision.colliding && !collision.willCollide){
            break;
        }
        velIntervalDistance = std::abs(velIntervalDistance);
        if(velIntervalDistance < intervalDistance){
            intervalDistance = velIntervalDistance;
            translationAxis = normal;
            sf::Vector2f center = getCenter();
            sf::Vector2f otherCenter = other.getCenter();
            sf::Vector2f centerDistance = sf::Vector2f(center.x - otherCenter.x, center.y - otherCenter.y);
            float dotProduct = centerDistance.x * translationAxis.x + centerDistance.y * translationAxis.y;
            if(dotProduct < 0){
                translationAxis = -translationAxis;
            }
        }
    }
    if(collision.willCollide){
        //get translation vector
        collision.translation = translationAxis * intervalDistance;
    }

    delete verts;
    delete otherVerts;
    return collision;
}

void Hitbox::draw(sf::RenderTarget& target){
    sf::RectangleShape rect(dimensions);
    rect.setFillColor(sf::Color(0, 255, 0, 100));
    rect.setPosition(position);
    rect.setOrigin(origin);
    rect.setRotation(rotation);
    target.draw(rect);
}
