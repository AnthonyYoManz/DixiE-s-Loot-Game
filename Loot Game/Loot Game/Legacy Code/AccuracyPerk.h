#pragma once

#include "Item.h"
#include "Perk.h"

class AccuracyPerk : public Perk{
public:
    void initialise(int _probability, int _rarity);
    void applyPerk(Item* _item);
};

