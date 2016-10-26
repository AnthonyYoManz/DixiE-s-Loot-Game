#include "bullet.h"

void Bullet::provideStats(ItemStats* itemStats, int ownerTags){
    stats = itemStats;
    speed = stats->bulletSpeed;
    if(ownerTags & OBJECT_PLAYER){
        wantedTags = OBJECT_PLAYER;
    }
    else{
        wantedTags = OBJECT_ENEMY;
    }
    wantedTags = wantedTags | OBJECT_TERRAIN;
}
void Bullet::setRotation(float _rotation){
    rotation = _rotation;
}
