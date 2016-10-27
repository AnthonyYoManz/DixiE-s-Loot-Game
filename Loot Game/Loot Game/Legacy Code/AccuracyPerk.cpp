#include "accuracyPerk.h"

void AccuracyPerk::initialise(int _probability, int _rarity){
    name = "Accuracy Bonus";
    type = PERK_TYPE_RANGED;
    probability = _probability;
    rarity = _rarity;
    amplification = 1.0f;
    perks.push_back(this);
}

void AccuracyPerk::applyPerk(Item* item){
    ItemStats& stats = item->modifiedStats;
    stats.accuracy += 10 * amplification;
    if(stats.accuracy > 100){
        stats.accuracy = 100;
    }
}
