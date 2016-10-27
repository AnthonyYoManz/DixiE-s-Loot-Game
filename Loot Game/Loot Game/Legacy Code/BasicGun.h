#ifndef ANT_BASIC_GUN

#include "entity.h"
#include "item.h"

class BasicGun : public Item{
public:
    virtual void initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
    void update();
    void handleCollision(SceneObject* object){}
    void draw(sf::RenderTarget& target);
    void cleanup();
    void activate(bool primary);

    void shoot();
};

#define ANT_BASIC_GUN
#endif // ANT_BASIC_GUN
