#ifndef ANT_SCENE

#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"
#include "gameState.h"

class SceneObject;

class Scene : public GameState{
protected:
    std::vector<SceneObject*> objectList;
    std::vector<unsigned int> removalList;
    std::vector<unsigned int> uncleanRemovalList;
    sf::Vector2f cameraPosition;
    sf::Vector2f cameraOffset;
    unsigned int currentHandle;

    void processRemovalList();
    void processUncleanRemovalList();
    void removeObjectFromList(unsigned int handle);
public:
    virtual void initialise(Game* _game) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual void cleanup() = 0;

    void addObject(SceneObject* object, sf::Vector2f position = sf::Vector2f(0, 0));
    void removeObject(unsigned int handle);
    void uncleanRemoveObject(unsigned int handle);
    void moveCamera(float x, float y);
    void offsetCamera(float x, float y);

    sf::Vector2f getCameraPosition();
    unsigned int getObjectCount();
    SceneObject* getObjectByID(unsigned int objectID);
    SceneObject* getObjectByHandle(unsigned int handle);
};

#define ANT_SCENE
#endif // ANT_SCENE
