#include "WeaponObject.h"

/*

*/

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
