#include "Hitbox.h"
#include <math.h>
#include <limits>

void Hitbox::update(sf::Vector2f _position, float _rotation, sf::Vector2f _velocity){
    m_position = _position;
    m_rotation = -_rotation;
    m_velocity = _velocity;
}

bool Hitbox::checkAABB(Hitbox other){
    float thisCenterX = m_position.x - m_origin.x + m_dimensions.x/2;
    float otherCenterX = other.m_position.x - other.m_origin.x + other.m_dimensions.x/2;
    float thisCenterY = m_position.y - m_origin.y + m_dimensions.y/2;
    float otherCenterY = other.m_position.y - other.m_origin.y + other.m_dimensions.y/2;
    bool xCollision = (std::abs(thisCenterX - otherCenterX) <= m_dimensions.x/2 + other.m_dimensions.x/2);
    bool yCollision = (std::abs(thisCenterY - otherCenterY) <= m_dimensions.y/2 + other.m_dimensions.y/2);
    return xCollision && yCollision;
}

sf::Vector2f Hitbox::getCenter(){
    sf::Vector2f center = sf::Vector2f(m_position.x - m_origin.x + m_dimensions.x/2, m_position.y - m_origin.y + m_dimensions.y/2);
    sf::Transform transformation = sf::Transform::Identity;
    transformation.rotate(m_rotation, m_position);
    center = transformation * center;
    return center;
}

sf::Vector2f* Hitbox::getVertices(){
    sf::Vector2f* vertices = new sf::Vector2f[4];
    vertices[0] = sf::Vector2f(m_position.x - m_origin.x, m_position.y - m_origin.y);
    vertices[1] = sf::Vector2f(m_position.x - m_origin.x + m_dimensions.x, m_position.y - m_origin.y);
    vertices[2] = sf::Vector2f(m_position.x - m_origin.x + m_dimensions.x, m_position.y - m_origin.y + m_dimensions.y);
    vertices[3] = sf::Vector2f(m_position.x - m_origin.x , m_position.y - m_origin.y + m_dimensions.y);
    sf::Transform transformation = sf::Transform::Identity;
    transformation.rotate(m_rotation, m_position);
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
    collision.m_colliding = true;
    collision.m_willCollide = true;
    collision.m_translation = sf::Vector2f(0, 0);

    float intervalDistance = std::numeric_limits<float>::max();
    sf::Vector2f translationAxis = sf::Vector2f(0, 0);

    sf::Vector2f relativeVelocity = m_velocity - other.m_velocity;

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
            collision.m_colliding = false;
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
            collision.m_willCollide = false;
        }
        if(!collision.m_colliding && !collision.m_willCollide){
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
    if(collision.m_willCollide){
        //get translation vector
        collision.m_translation = translationAxis * intervalDistance;
    }

    delete verts;
    delete otherVerts;
    return collision;
}

void Hitbox::draw(sf::RenderTarget& target){
    sf::RectangleShape rect(m_dimensions);
    rect.setFillColor(sf::Color(0, 255, 0, 100));
    rect.setPosition(m_position);
    rect.setOrigin(m_origin);
    rect.setRotation(m_rotation);
    target.draw(rect);
}
