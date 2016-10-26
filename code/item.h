#ifndef ANT_ITEM

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "game.h"
#include "scene.h"
#include "sceneObject.h"
#include "perk.h"
#include "timer.h"

class Entity;
class Launcher;
class Modifier;

enum ItemType{
    ITEM_TYPE_ARMOUR,
    ITEM_TYPE_RANGED,
    ITEM_TYPE_MELEE
};

struct ItemStats{
    float rateOfFire; //shots per second
    float damage;
    float DPS; //damage*simultaneousShots*rateOfFire
    int accuracy; //percentage
    float range;
    float bulletSpeed;
    float maxAmmo; //-1 for infinite (i.e. melee weapons)
    float magSize; //-1 for infinite
    float recoil;
    float knockback;
    float delay; //Delay before self destruction after reaching max range
    float secondaryCooldown;
    int simultaneousShots;
    bool piercing;
    bool bouncing;
    bool explosive;
    Launcher* launcher; //Creates bullets
    std::vector <Modifier*> modifiers;  //Appends bullet functionality
};

class Item : public SceneObject{
protected:
    ItemType type;
    ItemStats baseStats;
    unsigned int rarity;
    Entity* owner;
    std::vector<std::string> perkList;
    Timer timer[2];

    void setBaseStatsFromFile(std::string filename);
    void acquirePerks();
    void assignRarity();
public:
    ItemStats modifiedStats;

    virtual void initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0)) = 0;
    virtual void handleEvents(){}
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual void cleanup() = 0;
    virtual void activate(bool primary) = 0;

    bool onScreen();
    void drop();
    void setOwner(Entity* newOwner);
    unsigned int getOwnerHandle();
    unsigned int getRarity();
    unsigned int getPerkListSize();
    std::string getPerkName(unsigned int perkID);
};

#define ANT_ITEM
#endif // ANT_ITEM
