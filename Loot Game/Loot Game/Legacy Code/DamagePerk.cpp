#include "damagePerk.h"
void DamagePerk::initialise(int _probability, int _rarity){
    type = PERK_TYPE_RANGED;
    name = "Damage Bonus";
    amplification = 1.0f;
    probability = _probability;
    rarity = _rarity;
    perks.push_back(this);
}
void DamagePerk::applyPerk(Item* item){
    ItemStats& stats = item->modifiedStats;
    stats.damage += 5 * amplification;
    stats.DPS = stats.damage * stats.simultaneousShots * stats.rateOfFire;
}
