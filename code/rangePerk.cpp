#include "rangePerk.h"

void RangePerk::initialise(int _probability, int _rarity){
    type = PERK_TYPE_RANGED;
    name = "Range Bonus";
    amplification = 1.0f;
    probability = _probability;
    rarity = _rarity;
    perks.push_back(this);
}
void RangePerk::applyPerk(Item* item){
    ItemStats& stats = item->modifiedStats;
    stats.range += 25 * amplification;
}
