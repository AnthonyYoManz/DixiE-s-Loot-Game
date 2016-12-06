#pragma once
#include "ItemObject.h"
#include "Counter.h"

struct WeaponStats
{
	//Automatic
	bool m_automatic;

	//For burst fire
	unsigned int m_shotsPerTrigger;
	unsigned int m_shotCooldown;

	//Damage per hit
	float m_damage;

	//Rate of fire
	unsigned int m_attackCooldown;

	//Time after clicking before gun fires
	unsigned int m_chargeTime;
	
	//Spread/Spray params
	float m_maxSpread;
	float m_minSpread;
	float m_spreadRate;
	float m_despreadRate;

	//Power of recoil
	float m_recoil;

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

enum class AttackStage
{
	READY,
	STARTUP,
	ATTACK,
	COOLDOWN
};

class WeaponObject : public ItemObject
{
protected:
	//Stats before any changes
	WeaponStats m_baseStats;
	//Stats after perks are applied
	WeaponStats m_perkedStats;
	//Timer that manages attack cooldown
	Counter m_cooldownTimer;
	//Timer that manages reloading
	Counter m_reloadTimer;
	//Timer that manages charge time
	Counter m_chargeTimer;
	//Time that manages cooldown between shots
	Counter m_shotTimer;
	//Counter for current number of shots
	Counter m_shotCounter;
	//Current stage of attacking
	AttackStage m_attackStage;

	//Current ammo in clip
	unsigned int m_currentAmmo;
	//Current spread amount
	float m_spread;
	//Trigger held
	bool m_triggerDown;
	//Trigger pulled
	bool m_triggerPulled;

	void shoot(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	virtual void fire(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _projectiles) = 0;
public:
	//void applyPerks();
	virtual void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position);
	virtual void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	virtual void attack(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	void setTriggerDown(bool _down);
};