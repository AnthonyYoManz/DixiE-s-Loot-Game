#ifndef ANT_BASIC_LAUNCHER

#include "launcher.h"

class BasicLauncher : public Launcher{
public:
    Bullet* createBullet(unsigned int ownerHandle);
};

#define ANT_BASIC_LAUNCHER
#endif // ANT_BASIC_LAUNCHER
