#ifndef ANT_SPRAY_PERK

#include "perk.h"
#include "item.h"

class SprayPerk : public Perk{
public:
    void initialise(int _probability, int _rarity);
    void applyPerk(Item* item);
};

#define ANT_SPRAY_PERK
#endif // ANT_SPRAY_PERK
