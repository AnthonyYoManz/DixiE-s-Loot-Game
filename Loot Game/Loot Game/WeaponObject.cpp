#include "WeaponObject.h"

void WeaponObject::update(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	if (!m_holder)
	{
		m_triggerDown = false;
		m_triggerPulled = false;
	}
	if (m_perkedStats.m_automatic && m_currentAmmo>0)
	{
		if (!m_triggerDown)
		{
			m_spread -= m_perkedStats.m_despreadRate;
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
		m_spread -= m_perkedStats.m_despreadRate;
	}
	if (m_spread > m_perkedStats.m_maxSpread)
	{
		m_spread = m_perkedStats.m_maxSpread;
	}
	if (m_spread < m_perkedStats.m_minSpread)
	{
		m_spread = m_perkedStats.m_minSpread;
	}
	if (m_reloadCounter.check() && m_currentAmmo < m_perkedStats.m_clipSize)
	{
		m_currentAmmo = m_perkedStats.m_clipSize;
	}
	m_cooldownCounter.add();
	m_reloadCounter.add();
	m_position += m_velocity + m_controlledVelocity;
	decelerate();
}

void WeaponObject::setTriggerDown(bool _down)
{
	if (!m_triggerDown && _down)
	{
		m_triggerPulled = true;
	}
	m_triggerDown = _down;
}
