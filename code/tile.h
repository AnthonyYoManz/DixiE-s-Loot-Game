#ifndef ANT_TILE

#include "sceneObject.h"

class Tile : public SceneObject{
public:
    virtual void initialise(Game* _game, Scene* _scene,
                            unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
    virtual void handleEvents(){}
    virtual void update(){}
    virtual void handleCollision(SceneObject* other, Collision collision){}
    virtual void draw(sf::RenderTarget& target);
    virtual void cleanup(){}
    virtual bool onScreen(){ return true; }
};

#define ANT_TILE
#endif // ANT_TILE
