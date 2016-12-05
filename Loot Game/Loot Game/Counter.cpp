#include "Counter.h"

Counter::Counter()
{
	m_count = 0;
	m_target = 0;
	m_paused = false;
}

void Counter::add(unsigned int _amount)
{
	if (!m_paused)
	{
		m_count += _amount;
	}
}

void Counter::setTarget(unsigned int _target)
{
	m_target = _target;
}

void Counter::pause()
{
	m_paused = true;
}

void Counter::resume()
{
	m_paused = false;
}

void Counter::restart()
{
	m_count = 0;
}

void Counter::restart(unsigned int _target)
{
	m_count = 0;
	setTarget(_target);
}

unsigned int Counter::getCount()
{
	return m_count;
}

unsigned int Counter::getTarget()
{
	return m_target;
}

bool Counter::check()
{
	return m_count >= m_target;
}

bool Counter::isPaused()
{
	return m_paused;
}
