#pragma once
#include "ItemObject.h"

struct WeaponStats
{
	//Damage per hit
	float m_damage;

	//Rate of fire
	float m_attackSpeed;
	
	//Spread/Spray params
	float m_maxSpread;
	float m_minSpread;
	float m_spreadRate;

	//For shotguns and maybe more
	unsigned int m_simultaenousShots;
};

class WeaponObject : public ItemObject
{
protected:
	//Stats before any changes
	WeaponStats m_baseStats;
	//Stats after perks are applied
	WeaponStats m_perkedStats;
	//Timer that manages shot cooldown
	//Timer m_cooldownTimer;
public:
	//void applyPerks();
	//Shoot/Whack function
	virtual void attack(const GameInfo& _gameInfo, const StateInfo& _stateInfo) = 0;
};