#pragma once

#include "Bullet.h"
#include "Item.h"

class BasicBullet : public Bullet{
public:
    void initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
    void update();
    void handleCollision(SceneObject* _object){}
    void draw(sf::RenderTarget& _target);
    void cleanup();
    bool onScreen();
};
