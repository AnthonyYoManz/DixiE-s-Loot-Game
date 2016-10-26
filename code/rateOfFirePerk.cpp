#include "rateOfFirePerk.h"

void RateOfFirePerk::initialise(int _probability, int _rarity){
    type = PERK_TYPE_RANGED;
    name = "Rate of Fire Bonus";
    amplification = 1.0f;
    probability = _probability;
    rarity = _rarity;
    perks.push_back(this);
}
void RateOfFirePerk::applyPerk(Item* item){
    ItemStats& stats = item->modifiedStats;
    stats.rateOfFire += amplification;
}
