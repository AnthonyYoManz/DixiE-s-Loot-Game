#ifndef ANT_SCENE_OBJECT

#include <SFML/Graphics.hpp>
#include "game.h"
#include "gameObject.h"
#include "hitbox.h"
#include "scene.h"

enum ObjectTags{
    OBJECT_PLAYER = 1 << 0,
    OBJECT_ENEMY = 1 << 1,
    OBJECT_BULLET = 1 << 2,
    OBJECT_ITEM = 1 << 3,
    OBJECT_TERRAIN = 1 << 4
};

class SceneObject : public GameObject{
protected:
    int tags;
    int wantedTags; //tags used to filter collisions
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f cVelocity; //controlled velocity
    static const float maxVelocity;
    float rotation;
    float deceleration;
    unsigned int handle;
    Scene* scene;
    Hitbox hitbox;
    void decelerate();
public:
    virtual void initialise(Game* _game, Scene* _scene,
                            unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0)) = 0;
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void handleCollision(SceneObject* other, Collision collision){}
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual void cleanup() = 0;
    virtual bool onScreen() = 0;

    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();
    float getRotation();
    unsigned int getHandle();

    int getTags();
    int getWantedTags();
    Collision checkCollision(SceneObject* other);
    Hitbox getHitbox();
    void lookAt(sf::Vector2f point);
    void setVelocity(float x, float y);
    void changeVelocity(float x, float y);
};

#define ANT_SCENE_OBJECT
#endif // ANT_SCENE_OBJECT
