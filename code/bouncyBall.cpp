#include "bouncyBall.h"

void BouncyBall::initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position){
    game = _game;
    scene = _scene;
    handle = _handle;
    acceleration = 400;
    name = "ball";
    radius = 10;
    position = _position;
}
void BouncyBall::update(){
    changeVelocity(0, acceleration* game->deltaTime());

    position += velocity * game->deltaTime();
    if(position.y + radius > game->getWindowSize().y){
        position.y = game->getWindowSize().y - radius;
        setVelocity(velocity.x, -velocity.y);
    }
}
void BouncyBall::draw(sf::RenderTarget& target){
    sf::CircleShape circle;
    circle.setPosition(position-scene->getCameraPosition());
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setFillColor(sf::Color(0, 255, 0, 255));
    target.draw(circle);
}
void BouncyBall::cleanup(){
}
bool BouncyBall::onScreen(){
    sf::Vector2f camPos = scene->getCameraPosition();
    if(position.x - radius > camPos.x + game->getWindowSize().x){
        return false;
    }
    else if(position.x + radius < camPos.x){
        return false;
    }
    else if(position.y + radius < camPos.y){
        return false;
    }
    else if(position.y - radius > camPos.y + game->getWindowSize().y){
        return false;
    }
    return true;
}
