#ifndef ANT_BASIC_BULLET

#include "bullet.h"
#include "item.h"

class BasicBullet : public Bullet{
public:
    void initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
    void update();
    void handleCollision(SceneObject* object){}
    void draw(sf::RenderTarget& target);
    void cleanup();
    bool onScreen();
};

#define ANT_BASIC_BULLET
#endif // ANT_BASIC_BULLET
