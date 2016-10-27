#include "item.h"
#include "entity.h"
#include "launcher.h"
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>

void Item::setBaseStatsFromFile(std::string filename){
    std::ifstream reader;
    reader.open(filename.c_str());
    if(reader.is_open()){
        while(reader.good()){
            std::string line;
            std::getline(reader, line);
            std::size_t conPos; //contextual position
            conPos = line.find_first_of(" ");
            std::string variableName;
            if(conPos < line.size() && conPos >= 0){
                variableName = line.substr(0, conPos);
            }
            conPos = line.find_first_of("0123456789");
            std::string variableValue;
            if(conPos < line.size() && conPos >= 0){
                variableValue = line.substr(conPos-1, line.size()-1);
            }
            if(variableName == "rateOfFire"){
                baseStats.rateOfFire = atof(variableValue.c_str());
            }
            else if(variableName == "damage"){
                baseStats.damage = atof(variableValue.c_str());
            }
            else if(variableName == "accuracy"){
                baseStats.accuracy = atof(variableValue.c_str());
            }
            else if(variableName == "range"){
                baseStats.range = atof(variableValue.c_str());
            }
            else if(variableName == "bulletSpeed"){
                baseStats.bulletSpeed = atof(variableValue.c_str());
            }
            else if(variableName == "maxAmmo"){
                baseStats.maxAmmo = atoi(variableValue.c_str());
            }
            else if(variableName == "magSize"){
                baseStats.magSize = atoi(variableValue.c_str());
            }
            else if(variableName == "recoil"){
                baseStats.recoil = atof(variableValue.c_str());
            }
            else if(variableName == "knockback"){
                baseStats.knockback = atof(variableValue.c_str());
            }
            else if(variableName == "delay"){
                baseStats.delay = atof(variableValue.c_str());
            }
            else if(variableName == "secondaryCooldown"){
                baseStats.secondaryCooldown = atof(variableValue.c_str());
            }
            else if(variableName == "simultaneousShots"){
                baseStats.simultaneousShots = atoi(variableValue.c_str());
            }
            else if(variableName == "piercing"){
                if(atoi(variableValue.c_str()) != 0){
                    baseStats.piercing = true;
                }
            }
            else if(variableName == "bouncing"){
                if(atoi(variableValue.c_str()) != 0){
                    baseStats.bouncing = true;
                }
            }
            else if(variableName == "explosive"){
                if(atoi(variableValue.c_str()) != 0){
                    baseStats.explosive = true;
                }
            }
        }
        reader.close();
    }
    baseStats.DPS = baseStats.damage * baseStats.simultaneousShots * baseStats.rateOfFire;
    baseStats.launcher = NULL;
    tags = OBJECT_ITEM;
    wantedTags = OBJECT_PLAYER | OBJECT_TERRAIN;
}

void Item::acquirePerks(){
    modifiedStats = baseStats;
    int remainingDolla = rarity;
    std::vector<Perk*>* newPerkList = NULL;
    switch(type){
        case ITEM_TYPE_MELEE: newPerkList = Perk::getPerks(remainingDolla, PERK_TYPE_MELEE); break;
        case ITEM_TYPE_RANGED: newPerkList = Perk::getPerks(remainingDolla, PERK_TYPE_RANGED); break;
        default: newPerkList = Perk::getPerks(remainingDolla, PERK_TYPE_ARMOUR); break;
    }
    if(newPerkList != NULL){
        for(Perk* newPerk : *newPerkList){
            newPerk->applyPerk(this);
            std::stringstream perkName;
            perkName << newPerk->getName() << " Lv. " << newPerk->getAmplification();
            perkList.push_back(perkName.str());
        }
        delete newPerkList;
    }
    modifiedStats.damage += remainingDolla;
}
void Item::assignRarity(){
    rarity = 1 + (rand()%100);
}
bool Item::onScreen(){
    if(owner != NULL){
        return owner->onScreen();
    }
    return false;
}
void Item::drop(){
    owner = NULL;
    rotation = rand()%360;
    velocity = sf::Vector2f(rand()%300, rand()%300);
}
void Item::setOwner(Entity* newOwner){
    owner = newOwner;
    position = owner->getPosition();
    velocity = sf::Vector2f(0, 0);
}
unsigned int Item::getOwnerHandle(){
    if(owner != NULL){
        return owner->getHandle();
    }
    return 0;
}
unsigned int Item::getRarity(){
    return rarity;
}
unsigned int Item::getPerkListSize(){
    return perkList.size();
}
std::string Item::getPerkName(unsigned int perkID){
    return perkList.at(perkID);
}
