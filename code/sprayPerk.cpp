#include "sprayPerk.h"

void SprayPerk::initialise(int _probability, int _rarity){
    type = PERK_TYPE_RANGED;
    name = "Spray Shot";
    amplification = 1.0f;
    probability = _probability;
    rarity = _rarity;
    perks.push_back(this);
}
void SprayPerk::applyPerk(Item* item){
    ItemStats& stats = item->modifiedStats;
    stats.simultaneousShots += 5.f * amplification;
    stats.damage /= (4.f * amplification);
    stats.DPS = stats.rateOfFire * stats.simultaneousShots * stats.damage;
    stats.accuracy -= 3 * amplification;
    stats.recoil += (stats.recoil/2.f) * amplification;
    if(stats.accuracy < 1){
        stats.accuracy = 1;
    }
    if(stats.damage < 1){
        stats.damage = 1;
    }
}
