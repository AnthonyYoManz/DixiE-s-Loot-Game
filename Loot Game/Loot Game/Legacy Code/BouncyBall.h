#ifndef ANT_BOUNCY_BALL

#include <SFML/Graphics.hpp>
#include "game.h"
#include "scene.h"
#include "sceneObject.h"

class BouncyBall : public SceneObject{
private:
    float acceleration;
    float radius;
public:
    void initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position = sf::Vector2f(0, 0)) override;
    void update();
    void draw(sf::RenderTarget& target);
    void cleanup();
    bool onScreen();
};

#define ANT_BOUNCY_BALL
#endif // ANT_BOUNCY_BALL
