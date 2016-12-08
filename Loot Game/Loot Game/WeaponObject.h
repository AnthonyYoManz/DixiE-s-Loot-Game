#pragma once
#include "ItemObject.h"
#include "Counter.h"
#include "WeaponStats.h"
#include "Perk.h"
#include <vector>

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
	//Rarity
	int m_rarity;
	//Excess Rarity
	int m_excessRarity;
	//Current stage of attacking
	AttackStage m_attackStage;
	//Perk list
	std::vector<Perk*> m_perks;
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
	virtual void initialise(const GameInfo& _gameInfo, const StateInfo& _stateInfo, unsigned int _handle, sf::Vector2f _position);
	virtual void update(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	virtual void attack(const GameInfo& _gameInfo, const StateInfo& _stateInfo);
	void setTriggerDown(bool _down);
	void applyPerks();
	AttackStage getAttackStage() const;
};