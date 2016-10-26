#ifndef ANT_MODIFIER

#include <SFML/Graphics.hpp>
#include "game.h"
#include "scene.h"
#include "bullet.h"

class Modifier{
protected:
    Bullet* bullet;
    Game* game;
    Scene* scene;
public:
    void provideBullet(Bullet* _bullet);
    virtual void initialise(Game* _game, Scene* _scene) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual void cleanup() = 0;
};

#define ANT_MODIFIER
#endif // ANT_MODIFIER
