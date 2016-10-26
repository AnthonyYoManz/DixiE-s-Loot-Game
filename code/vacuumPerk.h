#ifndef ANT_VACUUM_PERK

#include "item.h"
#include "perk.h"

class VacuumPerk : public Perk{
public:
    void initialise(int _probability, int _rarity);
    void applyPerk(Item* item);
};

#define ANT_VACUUM_PERK
#endif // ANT_VACUUM_PERK
