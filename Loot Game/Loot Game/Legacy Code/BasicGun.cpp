#include "basicGun.h"
#include "bullet.h"
#include "basicLauncher.h"
#include <cstdlib>
#include <math.h>
#include <fstream>

void BasicGun::initialise(Game* _game, Scene* _scene, unsigned int _handle, sf::Vector2f _position){
    game = _game;
    scene = _scene;
    handle = _handle;
    position = _position;
    deceleration = 200;

    owner = NULL;
    type = ITEM_TYPE_RANGED;

    setBaseStatsFromFile("ass/guns/basicGun.gun");

    assignRarity();
    //delete someday:
    rarity = 100;
    acquirePerks();

    if(modifiedStats.launcher==NULL){
        modifiedStats.launcher = new BasicLauncher;
    }

    timer[0].start(1.f/modifiedStats.rateOfFire);
    timer[1].start(modifiedStats.secondaryCooldown);
}

void BasicGun::update(){
    if(owner==NULL){
        decelerate();
        position+=velocity * game->deltaTime();
    }
    else{
        position = owner->getPosition();
        rotation = owner->getRotation();
    }
}
void BasicGun::draw(sf::RenderTarget& target){
    sf::RectangleShape rect(sf::Vector2f(15, 5));
    rect.setPosition(position);
    rect.setOrigin(5, 2);
    rect.setFillColor(sf::Color(255, 0, 0));
    rect.setRotation(-rotation);
    target.draw(rect);
}
void BasicGun::cleanup(){
    delete modifiedStats.launcher;
}
void BasicGun::activate(bool primary){
    if(primary){
        if(timer[0].check()){
            shoot();
            timer[0].start(1.f/modifiedStats.rateOfFire);
        }
    }
    else{
        if(timer[1].check()){
            timer[1].start(modifiedStats.secondaryCooldown);
        }
    }
}
void BasicGun::shoot(){
    position = owner->getPosition();
    rotation = owner->getRotation();
    sf::Vector2f recoil;
    recoil.x = -cos(rotation * 3.14f / 180.f) * modifiedStats.recoil;
    recoil.y = sin(rotation * 3.14f / 180.f) * modifiedStats.recoil;
    owner->changeVelocity(recoil.x, recoil.y);
    for(int i=0; i<modifiedStats.simultaneousShots; i++){
        float randomOffset = (rand()%(int)(101-modifiedStats.accuracy)) - (101-modifiedStats.accuracy)/2.f;
        float angle = rotation + randomOffset;
        Bullet* bullet = modifiedStats.launcher->createBullet(getOwnerHandle());
        bullet->setRotation(angle);
        bullet->provideStats(&modifiedStats, owner->getTags());
        scene->addObject((SceneObject*)bullet, position);
    }
}
