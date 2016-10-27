#ifndef ANT_VACUUM_MODIFIER

#include "Modifier.h"

class VacuumModifier : public Modifier
{
public:
    float vacuumPower;
    float vacuumRadius;
    void initialise(Game* _game, Scene* _scene);
    void update();
    void draw(sf::RenderTarget& _target);
    void cleanup();
};

#define ANT_VACUUM_MODIFIER
#endif // ANT_VACUUM_MODIFIER
