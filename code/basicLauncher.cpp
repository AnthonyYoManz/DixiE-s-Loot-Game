#include "basicLauncher.h"
#include "basicBullet.h"

Bullet* BasicLauncher::createBullet(unsigned int ownerHandle){
    BasicBullet* basicBullet = new BasicBullet;
    basicBullet->ownerHandle = ownerHandle;
    return (Bullet*)basicBullet;
}
