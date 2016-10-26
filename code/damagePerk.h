#ifndef ANT_DAMAGE_PERK

#include "item.h"
#include "perk.h"

class DamagePerk : public Perk{
public:
    void initialise(int _probability, int _rarity);
    void applyPerk(Item* item);
};

#define ANT_DAMAGE_PERK
#endif // ANT_DAMAGE_PERK
