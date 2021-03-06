#include "vacuumPerk.h"
#include "vacuumModifier.h"

void VacuumPerk::initialise(int _probability, int _rarity)
{
    type = PERK_TYPE_RANGED;
    name = "Vacuum Shots";
    amplification = 1.0f;
    probability = _probability;
    rarity = _rarity;
    perks.push_back(this);
}

void VacuumPerk::applyPerk(Item* _item)
{
    ItemStats& stats = _item->modifiedStats;
    VacuumModifier* vacuumModifier = new VacuumModifier;
    vacuumModifier->vacuumPower = (1000.f / (stats.simultaneousShots * 0.7)) * amplification;
    vacuumModifier->vacuumRadius = 100.f * amplification;
    stats.modifiers.push_back((Modifier*)vacuumModifier);
    stats.delay = 3.f * amplification;
}
