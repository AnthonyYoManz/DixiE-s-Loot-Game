#ifndef ANT_RANGE_PERK

#include "item.h"
#include "perk.h"

class RangePerk : public Perk{
public:
    void initialise(int _probability, int _rarity);
    void applyPerk(Item* item);
};

#define ANT_RANGE_PERK
#endif // ANT_RANGE_PERK
