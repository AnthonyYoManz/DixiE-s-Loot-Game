#include "propulsionPerk.h"
#include "vacuumModifier.h"

void PropulsionPerk::initialise(int _probability, int _rarity){
    type = PERK_TYPE_RANGED;
    name = "Propulsive Shots";
    amplification = 1.0f;
    probability = _probability;
    rarity = _rarity;
    perks.push_back(this);
}

void PropulsionPerk::applyPerk(Item* item){
    ItemStats& stats = item->modifiedStats;
    VacuumModifier* vacuumModifier = new VacuumModifier;
    vacuumModifier->vacuumPower = (-1000.f / (stats.simultaneousShots * 0.7)) * amplification;
    vacuumModifier->vacuumRadius = 100.f * amplification;
    stats.modifiers.push_back((Modifier*)vacuumModifier);
    stats.delay = 3.f * amplification;
}

