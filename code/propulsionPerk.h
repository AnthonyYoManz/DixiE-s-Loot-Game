#ifndef ANT_PROPULSION_PERK

#include "item.h"
#include "perk.h"

class PropulsionPerk : public Perk{
public:
    void initialise(int _probability, int _rarity);
    void applyPerk(Item* item);
};

#define ANT_PROPULSION_PERK
#endif // ANT_PROPULSION_PERK
