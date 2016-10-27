#include <cstdlib>
#include "perk.h"
#include "item.h"

#include "rangePerk.h"
#include "recoilPerk.h"
#include "damagePerk.h"
#include "accuracyPerk.h"
#include "rateOfFirePerk.h"
#include "sprayPerk.h"
#include "propulsionPerk.h"
#include "vacuumPerk.h"

std::vector<Perk*> Perk::perks;
bool Perk::initialised = false;

//someday i'll figure out how to do this without being shit
void Perk::initialiseAll(){
    if(!initialised){
        Perk* propulsionPerk = new PropulsionPerk;
        propulsionPerk->initialise(1, 40);
        Perk* vacuumPerk = new VacuumPerk;
        vacuumPerk->initialise(1, 40);
        Perk* sprayPerk = new SprayPerk;
        sprayPerk->initialise(1, 30);
        Perk* accuracyPerk = new AccuracyPerk;
        accuracyPerk->initialise(1, 20);
        Perk* rateOfFirePerk = new RateOfFirePerk;
        rateOfFirePerk->initialise(1, 20);
        Perk* damagePerk = new DamagePerk;
        damagePerk->initialise(1, 10);
        Perk* rangePerk = new RangePerk;
        rangePerk->initialise(1, 10);
        Perk* recoilPerk = new RecoilPerk;
        recoilPerk->initialise(1, 10);
    }
    initialised = true;
}
void Perk::cleanup(){
    for(Perk* perk : perks){
        delete perk;
    }
    perks.clear();
    initialised = false;
}
#include <iostream>
std::vector<Perk*>* Perk::getPerks(int& payment, PerkType perkType){
    std::vector<Perk*>* returnPerkList = new std::vector<Perk*>;
    while(payment > cheapest){
        std::vector<Perk*> potentialPerks;
        int probabilityWeight = 0;
        for(Perk* perk : perks){
            if(perk->rarity <= payment && perk->type == perkType){
                potentialPerks.push_back(perk);
                probabilityWeight += perk->getProbability();
                perk->setAmplification(1);
            }
        }
        int cumulativeProbability = 0;
        if(potentialPerks.size()>0){
            for(unsigned int i=0; i<potentialPerks.size(); i++){
                if(rand()%probabilityWeight < potentialPerks.at(i)->getProbability()+cumulativeProbability){
                    returnPerkList->push_back(potentialPerks.at(i));
                    payment -= potentialPerks.at(i)->getRarity();
                    break;
                }
                cumulativeProbability += potentialPerks.at(i)->getProbability();
            }
        }
    }
    for(unsigned int i=0; i<returnPerkList->size(); i++){
        for(unsigned int j=i+1; j<returnPerkList->size(); j++){
            if(returnPerkList->at(i)->getName() == returnPerkList->at(j)->getName()){
                returnPerkList->at(i)->changeAmplification(1);
                returnPerkList->erase(returnPerkList->begin() + j);
                j--;
            }
        }
    }
    if(returnPerkList->size() != 0){
        return returnPerkList;
    }
    return NULL;
}

void Perk::setAmplification(float newAmp){
    amplification = newAmp;
}
void Perk::changeAmplification(float difference){
    amplification += difference;
}
int Perk::getAmplification(){
    return (int)amplification;
}
int Perk::getProbability(){
    return probability;
}
int Perk::getRarity(){
    return rarity;
}
std::string Perk::getName(){
    return name;
}
