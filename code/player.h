#ifndef ANT_PLAYER

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include "game.h"
#include "entity.h"

enum PlayerAction{
    PLAYER_RIGHT,
    PLAYER_LEFT,
    PLAYER_UP,
    PLAYER_DOWN,
    PLAYER_ACTIVATE_R1,
    PLAYER_ACTIVATE_R2,
    PLAYER_ACTIVATE_L1,
    PLAYER_ACTIVATE_L2
};

class Player : public Entity{
private:
    float radius;
    std::vector<Item*> inventory;
    std::map<PlayerAction, std::string>* actionMap;
public:
    void initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0));
    void handleEvents();
    void update();
    void handleCollision(SceneObject* object, Collision collision);
    void draw(sf::RenderTarget& target);
    void cleanup();
    void setControls(std::map<PlayerAction, std::string>* _actionMap);
};

#define ANT_PLAYER
#endif // ANT_PLAYER
