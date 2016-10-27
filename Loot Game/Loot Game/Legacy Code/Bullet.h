#ifndef ANT_BULLET

#include "sceneObject.h"
#include "item.h"

class Bullet : public SceneObject{
protected:
    sf::Clock lifeClock;
    float speed;
    sf::Vector2f prevPos;
    ItemStats* stats;
public:
    unsigned int ownerHandle;

    virtual void initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0)) = 0;
    virtual void handleEvents(){}
    virtual void handleCollision(SceneObject* object, Collision collision){} //fixme
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual void cleanup() = 0;
    virtual bool onScreen() = 0;

    void provideStats(ItemStats* itemStats, int ownerTags);
    void setRotation(float _rotation);
};

#define ANT_BULLET
#endif // ANT_BULLET
