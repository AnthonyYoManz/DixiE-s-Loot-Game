#ifndef ANT_RATE_OF_FIRE_PERK

#include "item.h"
#include "perk.h"

class RateOfFirePerk : public Perk{
public:
    void initialise(int _probability, int _rarity);
    void applyPerk(Item* item);
};

#define ANT_RATE_OF_FIRE_PERK
#endif // ANT_RATE_OF_FIRE_PERK
