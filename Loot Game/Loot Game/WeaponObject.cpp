#include "WeaponObject.h"

void WeaponObject::update(const GameInfo & _gameInfo, const StateInfo & _stateInfo)
{
	if (m_perkedStats.m_automatic)
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
	m_cooldownCounter.add();
}

void WeaponObject::setTriggerDown(bool _down)
{
	if (!m_triggerDown && _down)
	{
		m_triggerPulled = true;
	}
	m_triggerDown = _down;
}
