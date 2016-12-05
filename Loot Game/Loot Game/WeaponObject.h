#pragma once
#include "ItemObject.h"
#include "Counter.h"

struct WeaponStats
{
	//Automatic
	bool m_automatic;

	//Damage per hit
	float m_damage;

	//Rate of fire
	unsigned int m_attackCooldown;
	
	//Spread/Spray params
	float m_maxSpread;
	float m_minSpread;
	float m_spreadRate;
	float m_despreadRate;

	//Ammo params
	unsigned int m_clipSize;
	unsigned int m_ammoPerProjectile;
	unsigned int m_reloadTime;

	//Weapon Range
	int m_range;

	//Speed at which projectiles travel
	int m_projectileSpeed;

	//Draw spread lines
	bool m_aimGuide;

	//For shotguns and maybe more
	unsigned int m_projectilesPerShot;
};

class WeaponObject : public ItemObject
{
protected:
	//Stats before any changes
	WeaponStats m_baseStats;
	//Stats after perks are applied
	WeaponStats m_perkedStats;
	//Timer that manages shot cooldown
	Counter m_cooldownCounter;
	//Timer that manages reloading
	Counter m_reloadCounter;
	//Current ammo in clip
	unsigned int m_currentAmmo;
	//Current spread amount
	float m_spread;
	//Trigger held
	bool m_triggerDown;
	//Trigger pulled
	bool m_triggerPulled;
public:
	//void applyPerks();
	//Shoot/Whack function
	virtual void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	virtual void attack(const GameInfo& _gameInfo, const StateInfo& _stateInfo) = 0;
	void setTriggerDown(bool _down);
};