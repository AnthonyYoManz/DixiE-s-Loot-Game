#include "SpreadDampeningPerk.h"

void SpreadDampeningPerk::initialise(int _value, int _droprate, int _maxStacks)
{
	Perk::initialise(_value, _droprate, _maxStacks);
	m_name = "Spread Dampening Perk";
	m_statsMod.m_spreadRate = -0.8;
}
