#ifndef ANT_LAUNCHER

#include "bullet.h"

class Launcher{
public:
    virtual Bullet* createBullet(unsigned int ownerHandle) = 0;
};

#define ANT_LAUNCHER
#endif // ANT_LAUNCHER
