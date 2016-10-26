#ifndef ANT_TEST_SCENE

#include "scene.h"

class TestScene : public Scene{
public:
    void initialise(Game* _game);
    void update();
    void draw(sf::RenderTarget& target);
    void cleanup();
};

#define ANT_TEST_SCENE
#endif // ANT_TEST_SCENE
