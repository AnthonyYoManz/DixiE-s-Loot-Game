#ifndef ANT_ACCURACY_PERK

#include "item.h"
#include "perk.h"

class AccuracyPerk : public Perk{
public:
    void initialise(int _probability, int _rarity);
    void applyPerk(Item* item);
};

#define ANT_ACCURACY_PERK
#endif // ANT_ACCURACY_PERK
