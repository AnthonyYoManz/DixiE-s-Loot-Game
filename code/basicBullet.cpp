#include "basicBullet.h"
#include "modifier.h"

void BasicBullet::initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position){
    game = _game;
    scene = _scene;
    handle = _handle;
    position = _position;
    prevPos = position;
    deceleration = 900;
    lifeClock.restart();
    tags = OBJECT_BULLET;
    wantedTags = OBJECT_PLAYER | OBJECT_ENEMY;
    for(unsigned int i=0; i<stats->modifiers.size(); i++){
        stats->modifiers.at(i)->initialise(game, scene);
        stats->modifiers.at(i)->provideBullet(this);
    }
}
void BasicBullet::update(){
    cVelocity.x = cos(rotation * 3.14f / 180.f) * speed;
    cVelocity.y = -sin(rotation * 3.14f / 180.f) * speed;
    for(unsigned int i=0; i<stats->modifiers.size(); i++){
        stats->modifiers.at(i)->update();
    }
    decelerate();
    prevPos = position;
    position += cVelocity * game->deltaTime();
    position += velocity * game->deltaTime();
    if(lifeClock.getElapsedTime().asSeconds()*speed >= stats->range){
        scene->removeObject(handle);
    }
}
void BasicBullet::draw(sf::RenderTarget& target){
    sf::CircleShape circle;
    circle.setRadius(3);
    circle.setFillColor(sf::Color(255, 0, 0, 255));
    circle.setPosition(position - scene->getCameraPosition());
    circle.setOrigin(3, 3);
    target.draw(circle);
    for(unsigned int i=0; i<stats->modifiers.size(); i++){
        stats->modifiers.at(i)->draw(target);
    }
}
void BasicBullet::cleanup(){
}
bool BasicBullet::onScreen(){
    return true;
}
