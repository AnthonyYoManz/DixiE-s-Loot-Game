#include "SprayPerk.h"

void SprayPerk::initialise(int _value, int _droprate, int _maxStacks)
{
	Perk::initialise(_value, _droprate, _maxStacks);
	m_name = "Spray Perk";
	m_statsMod.m_projectilesPerShot = +1;
}
