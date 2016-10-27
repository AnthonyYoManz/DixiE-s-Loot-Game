#include "recoilPerk.h"

void RecoilPerk::initialise(int _probability, int _rarity){
    type = PERK_TYPE_RANGED;
    name = "Recoil Reduction";
    amplification = 1.0f;
    probability = _probability;
    rarity = _rarity;
    perks.push_back(this);
}
void RecoilPerk::applyPerk(Item* item){
    ItemStats& stats = item->modifiedStats;
    stats.recoil -= 8 * amplification;
    if(stats.recoil < 0){
        stats.recoil = 0;
    }
}
