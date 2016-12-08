#include "WeaponObject.h"
#include "Algorithms.h"

void WeaponObject::shoot(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	unsigned int projectiles = m_perkedStats.m_projectilesPerShot;
	if (projectiles > m_currentAmmo)
	{
		projectiles = m_currentAmmo;
	}
	fire(_gameInfo, _stateInfo, projectiles);
	m_currentAmmo -= projectiles * m_perkedStats.m_ammoPerProjectile;
	m_spread += m_perkedStats.m_spreadRate;
	if (m_spread > m_perkedStats.m_maxSpread)
	{
		m_spread = m_perkedStats.m_maxSpread;
	}
	if (m_spread < m_perkedStats.m_minSpread)
	{
		m_spread = m_perkedStats.m_minSpread;
	}
	m_shotCounter.add();
	m_shotTimer.restart(m_perkedStats.m_shotCooldown);
}

void WeaponObject::applyPerks()
{
	m_perkedStats = m_baseStats;
	for (Perk* perk : m_perks)
	{
		m_perkedStats.m_aimGuide = m_perkedStats.m_aimGuide || perk->getStatsMod().m_aimGuide;

		m_perkedStats.m_ammoPerProjectile += perk->getStatsMod().m_ammoPerProjectile;

		m_perkedStats.m_attackCooldown += perk->getStatsMod().m_attackCooldown * perk->getStackCount();
		m_perkedStats.m_attackCooldown = max(m_perkedStats.m_attackCooldown, 0);	//Ensure minimum of 0 frames attack cooldown

		m_perkedStats.m_automatic = m_perkedStats.m_automatic || perk->getStatsMod().m_automatic;

		m_perkedStats.m_chargeTime += perk->getStatsMod().m_chargeTime * perk->getStackCount();
		m_perkedStats.m_chargeTime = max(m_perkedStats.m_chargeTime, 0); //Ensure minimum of 0 frames charge time

		m_perkedStats.m_clipSize += perk->getStatsMod().m_clipSize * perk->getStackCount();
		m_perkedStats.m_clipSize = max(m_perkedStats.m_clipSize, 1);	//Ensure minimum of 1 ammo

		m_perkedStats.m_damage += perk->getStatsMod().m_damage * perk->getStackCount();
		m_perkedStats.m_damage = max(m_perkedStats.m_damage, 1.f);	//Ensure minimum of 1 damage

		m_perkedStats.m_despreadRate += perk->getStatsMod().m_despreadRate * perk->getStackCount();
		m_perkedStats.m_despreadRate = max(m_perkedStats.m_despreadRate, 0.01f);	//Ensure minimum of 0.01 despread rate

		m_perkedStats.m_maxSpread += perk->getStatsMod().m_maxSpread * perk->getStackCount();
		m_perkedStats.m_maxSpread = max(m_perkedStats.m_maxSpread, 0.f);	//Ensure minimum of 0 degrees max spread

		m_perkedStats.m_minSpread += perk->getStatsMod().m_minSpread * perk->getStackCount();
		m_perkedStats.m_minSpread = max(m_perkedStats.m_minSpread, 0.f);	//Ensure minimum of 0 degrees min spread

		m_perkedStats.m_projectileSpeed += perk->getStatsMod().m_projectileSpeed * perk->getStackCount();
		m_perkedStats.m_projectileSpeed = max(m_perkedStats.m_projectileSpeed, 1);	//Ensure minimum projectile speed of 1 pix per sec

		m_perkedStats.m_projectilesPerShot += perk->getStatsMod().m_projectilesPerShot * perk->getStackCount();
		m_perkedStats.m_projectilesPerShot = max(m_perkedStats.m_projectilesPerShot, 1);	//Ensure minimum of 1 projectile per shot

		m_perkedStats.m_range += perk->getStatsMod().m_range * perk->getStackCount();
		m_perkedStats.m_range = max(m_perkedStats.m_range, m_perkedStats.m_projectileSpeed + 1);	//Ensure projectiles exist for at least one frame of movement

		m_perkedStats.m_recoil += perk->getStatsMod().m_recoil * perk->getStackCount();
		m_perkedStats.m_recoil = max(m_perkedStats.m_recoil, 0.f);	//Ensure minimum recoil of 0 (recoil doesn't pull forwards duh)

		m_perkedStats.m_reloadTime += perk->getStatsMod().m_reloadTime * perk->getStackCount();
		m_perkedStats.m_reloadTime = max(m_perkedStats.m_reloadTime, 0);	//Ensure minimum reload time of 0 frames

		m_perkedStats.m_shotCooldown += perk->getStatsMod().m_shotCooldown * perk->getStackCount();
		m_perkedStats.m_shotCooldown = max(m_perkedStats.m_shotCooldown, 0);	//Ensure minimum shot cooldown of 0 frames

		m_perkedStats.m_shotsPerTrigger += perk->getStatsMod().m_shotsPerTrigger * perk->getStackCount();
		m_perkedStats.m_shotsPerTrigger = max(m_perkedStats.m_shotsPerTrigger, 1);	//Ensure minimum shots per trigger of 1

		m_perkedStats.m_spreadRate += perk->getStatsMod().m_spreadRate * perk->getStackCount();
		m_perkedStats.m_spreadRate = max(m_perkedStats.m_spreadRate, 0.f);	//Ensure minimum spread rate of 0
	}
}

AttackStage WeaponObject::getAttackStage() const
{
	return m_attackStage;
}

void WeaponObject::initialise(const GameInfo & _gameInfo, const StateInfo & _stateInfo, unsigned int _handle, sf::Vector2f _position)
{
	ItemObject::initialise(_gameInfo, _stateInfo, _handle, _position);
	m_attackStage = AttackStage::READY;

	m_currentAmmo = 0;
	m_triggerDown = false;
	m_spread = m_perkedStats.m_minSpread;

	m_cooldownTimer.setTarget(m_perkedStats.m_attackCooldown);
	m_reloadTimer.setTarget(m_perkedStats.m_reloadTime);
	m_shotCounter.setTarget(m_perkedStats.m_shotsPerTrigger);
	m_shotTimer.setTarget(m_perkedStats.m_shotCooldown);

	m_rarity = 10;// rand() % 100 + 1; //rand() % x + 1 where x is max rarity

	m_perks = Perk::getPerks(m_rarity);
	_gameInfo.m_debug->print("Rarity: " + std::to_string(m_rarity) + "\n");
	int rarityUsed = 0;
	for (auto* perk : m_perks)
	{
		_gameInfo.m_debug->print("Perk acquired: " + perk->getName() + "\n");
		rarityUsed += perk->getValue() * perk->getStackCount();
	}
	m_excessRarity = m_rarity - rarityUsed;
	_gameInfo.m_debug->print("Excess rarity: " + std::to_string(m_excessRarity) + "\n");
	applyPerks();
}

void WeaponObject::update(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	if (!m_holder)
	{
		m_triggerDown = false;
		m_triggerPulled = false;
		m_attackStage = AttackStage::READY;
	}
	if (m_perkedStats.m_automatic && m_currentAmmo>0)
	{
		if (!m_triggerDown)
		{
			if (m_attackStage == AttackStage::READY)
			{
				m_spread -= m_perkedStats.m_despreadRate;
			}
		}
		else
		{
			attack(_gameInfo, _stateInfo);
		}
	}
	else
	{
		if (m_triggerPulled)
		{
			m_triggerPulled = false;
			attack(_gameInfo, _stateInfo);
		}
		if (m_attackStage == AttackStage::READY || m_attackStage == AttackStage::COOLDOWN)
		{
			m_spread -= m_perkedStats.m_despreadRate;
		}
	}
	if (m_spread > m_perkedStats.m_maxSpread)
	{
		m_spread = m_perkedStats.m_maxSpread;
	}
	if (m_spread < m_perkedStats.m_minSpread)
	{
		m_spread = m_perkedStats.m_minSpread;
	}
	if (m_reloadTimer.check() && m_currentAmmo < m_perkedStats.m_clipSize)
	{
		m_currentAmmo = m_perkedStats.m_clipSize;
	}
	if (m_attackStage == AttackStage::ATTACK)
	{
		if (m_shotTimer.check())
		{
			shoot(_gameInfo, _stateInfo);
		}
		if (m_shotCounter.check())
		{
			m_attackStage = AttackStage::COOLDOWN;
			m_cooldownTimer.restart(m_perkedStats.m_attackCooldown);
		}
	}
	if (m_attackStage == AttackStage::COOLDOWN)
	{
		if (m_cooldownTimer.check())
		{
			m_attackStage = AttackStage::READY;
		}
	}
	if (m_attackStage == AttackStage::STARTUP)
	{
		if (m_chargeTimer.check())
		{
			m_attackStage = AttackStage::ATTACK;
			m_shotCounter.restart(m_perkedStats.m_shotsPerTrigger);
			shoot(_gameInfo, _stateInfo);
		}
	}
	if (m_attackStage != AttackStage::READY)
	{
		m_reloadTimer.restart(m_perkedStats.m_reloadTime);
	}
	m_cooldownTimer.add();
	m_reloadTimer.add();
	m_chargeTimer.add();
	m_shotTimer.add();
	m_position += m_velocity + m_controlledVelocity;
	decelerate();
}

void WeaponObject::attack(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	if (m_attackStage == AttackStage::READY && m_currentAmmo > 0)
	{
		m_attackStage = AttackStage::STARTUP;
		m_chargeTimer.restart(m_perkedStats.m_chargeTime);
	}
}

void WeaponObject::setTriggerDown(bool _down)
{
	if (!m_triggerDown && _down)
	{
		m_triggerPulled = true;
	}
	m_triggerDown = _down;
}
