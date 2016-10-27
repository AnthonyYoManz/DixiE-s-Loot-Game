#ifndef ANT_PERK
#include <string>
#include <vector>

class Item;

enum PerkType{
    PERK_TYPE_ARMOUR,
    PERK_TYPE_RANGED,
    PERK_TYPE_MELEE
};

class Perk{
protected:
    std::string name;
    static std::vector<Perk*> perks;
    static bool initialised;
    int probability; //Percentage
    int rarity;
    float amplification;
    PerkType type;
public:
    static const int cheapest = 10;

    static void initialiseAll();
    static void cleanup();
    static std::vector<Perk*>* getPerks(int& payment, PerkType perkType);

    virtual void initialise(int _probability, int _rarity) = 0;

    void setAmplification(float newAmp);
    void changeAmplification(float difference);
    std::string getName();
    int getAmplification();
    int getProbability();
    int getRarity();

    virtual void applyPerk(Item* item) = 0;
};

#define ANT_PERK
#endif // ANT_PERK
