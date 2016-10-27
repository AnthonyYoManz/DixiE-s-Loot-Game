#ifndef ANT_RECOIL_PERK

#include "perk.h"
#include "item.h"

class RecoilPerk : public Perk{
public:
    void initialise(int _probability, int _rarity);
    void applyPerk(Item* item);
};

#define ANT_RECOIL_PERK
#endif // ANT_RECOIL_PERK
