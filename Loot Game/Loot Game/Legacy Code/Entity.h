#ifndef ANT_ENTITY

#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"
#include "scene.h"
#include "sceneObject.h"
#include "item.h"

class Entity : public SceneObject{
protected:
    float maxHealth;
    float health;
    sf::IntRect bounds;
    Item* rightHandItem;
    Item* leftHandItem;
    Item* headItem;
    Item* bodyItem;
    Item* miscItem;
    void initialiseItems();
    void updateItems();
    void cleanupItems();
public:
    float maxMoveSpeed;
    float getHealth();
    void inflictDamge(float damage);
    bool onScreen();

    virtual void handleEvents(){}
};

#define ANT_ENTITY
#endif // ANT_ENTITY
