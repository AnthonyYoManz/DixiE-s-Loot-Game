#include "BurstPerk.h"

void BurstPerk::initialise(int _value, int _droprate, int _maxStacks)
{
	Perk::initialise(_value, _droprate, _maxStacks);
	m_name = "Burst Perk";
	m_statsMod.m_shotsPerTrigger = +2;
	m_statsMod.m_shotCooldown = -1;
}
